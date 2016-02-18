/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"
#include "ScenarioTracerWithStarter.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

// using宣言
using ev3api::GyroSensor;
using ev3api::TouchSensor;
using ev3api::Motor;
using ev3api::Clock;

// Device objects
// オブジェクトを静的に確保する
GyroSensor  gGyroSensor(PORT_4);
TouchSensor gTouchSensor(PORT_1);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
Clock       gClock;

// オブジェクトの定義
static BalancingWalker *gBalancingWalker;
static Balancer        *gBalancer;
static Starter         *gStarter;
static SimpleTimer     *gSimpleTimer;
static Scenario        *gScenario;
static ScenarioTracer  *gScenarioTracer;
static ScenarioTracerWithStarter *gScenarioTracerWithStarter;

// scene object
static Scene gScenes[] = {
    {-30, 1250, 0 },  // 左旋回1.25秒
    {0,   5000, 0 },  // 直進5秒
    {-30, 1250, 0 },  // 左旋回1.25秒
    {0,   2500, 0 }   // 直進2.5秒
};

/**
 * EV3システム生成
 */
static void user_system_create() {
    // オブジェクトの作成
    gBalancer        = new Balancer();
    gBalancingWalker = new BalancingWalker(gGyroSensor,
                                           gLeftWheel,
                                           gRightWheel,
                                           gBalancer);
    gStarter         = new Starter(gTouchSensor);
    gSimpleTimer     = new SimpleTimer(gClock);
    gScenario        = new Scenario(0);
    gScenarioTracer  = new ScenarioTracer(gBalancingWalker,
                                          gScenario,
                                          gSimpleTimer);
    gScenarioTracerWithStarter =
        new ScenarioTracerWithStarter(gScenarioTracer,
                                      gStarter);

    // シナリオを構築する
    for (uint32_t i = 0; i < (sizeof(gScenes)/sizeof(gScenes[0])); i++) {
        gScenario->add(&gScenes[i]);
    }
    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();

    delete gScenarioTracerWithStarter;
    delete gScenarioTracer;
    delete gScenario;
    delete gSimpleTimer;
    delete gStarter;
    delete gBalancingWalker;
    delete gBalancer;
}

/**
 * トレース実行タイミング
 */
void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(TRACER_TASK);
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(EV3_CYC_TRACER);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        gScenarioTracerWithStarter->run();  // 倒立走行
    }

    ext_tsk();
}
