#ifndef _NETMF_H_
#define _NETMF_H_

/*
 *  �e�^�X�N�̗D��x�̒�`
 */

#define MAIN_PRIORITY	5		/* ���C���^�X�N�̗D��x */
								/* HIGH_PRIORITY��荂�����邱�� */

#define HIGH_PRIORITY	9		/* ���s���s�����^�X�N�̗D��x */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

/*
 *  �^�[�Q�b�g�Ɉˑ�����\���̂���萔�̒�`
 */

#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* �������͂���V���A���|�[�gID */
#endif /* TASK_PORTID */

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* �^�X�N�̃X�^�b�N�T�C�Y */
#endif /* STACK_SIZE */

// extern void ApplicationEntryPoint();
// extern void task_netmf(intptr_t exinf);

#endif /* _NETMF_H_ */

