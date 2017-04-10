//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------


#include "tinyhal.h"
#include "Core.h"
#include "CQ_NETMF_UTIL.h"
#include "CQ_NETMF_UTIL_CQ_NETMF_UTIL_EEHeap.h"

using namespace CQ::NETMF::UTIL;

extern struct CLR_RT_ExecutionEngine g_CLR_RT_ExecutionEngine;
static struct CLR_RT_HeapCluster *m_heap_cluster = (CLR_RT_HeapCluster *)NULL;

UINT32 EEHeap::EEHeap_get_top( HRESULT &hr )
{
    if (m_heap_cluster == (CLR_RT_HeapCluster *)NULL)
    	m_heap_cluster = (struct CLR_RT_HeapCluster *)g_CLR_RT_ExecutionEngine.m_heap.FirstNode();
    return (UINT32)m_heap_cluster->m_payloadStart;
}

UINT32 EEHeap::EEHeap_get_size( HRESULT &hr )
{
    UINT32 retVal = 0; 
    return retVal;
}

UINT32 EEHeap::EEHeap_get_next( UINT32 param0, HRESULT &hr )
{
    CLR_RT_HeapBlock_Node *ptr = (CLR_RT_HeapBlock_Node*)param0;
    ptr += ptr->DataSize();
    return (UINT32)ptr;
}

UINT32 EEHeap::EEHeap_get_prev( UINT32 param0, HRESULT &hr )
{
    CLR_RT_HeapBlock_Node *ptr = (CLR_RT_HeapBlock_Node *)param0;
    CLR_RT_HeapBlock_Node *prev = ptr->Prev();
    return (UINT32)prev;
}

UINT32 EEHeap::EEHeap_get_last( HRESULT &hr )
{
    UINT32 retVal;
    if (m_heap_cluster == (CLR_RT_HeapCluster *)NULL)
    	m_heap_cluster = (struct CLR_RT_HeapCluster *)g_CLR_RT_ExecutionEngine.m_heap.FirstNode();
    retVal = (UINT32)m_heap_cluster->m_payloadEnd;
    return retVal;
}

UINT32 EEHeap::EEHeap_get_hb_flags( UINT32 param0, HRESULT &hr )
{
    UINT32 retVal = (UINT32)((CLR_RT_HeapBlock *)param0)->DataFlags();
    return retVal;
}

UINT32 EEHeap::EEHeap_get_hb_size( UINT32 param0, HRESULT &hr )
{
    UINT32 retVal = (UINT32)((CLR_RT_HeapBlock *)param0)->DataSize();
    return retVal;
}

UINT32 EEHeap::EEHeap_get_hb_type( UINT32 param0, HRESULT &hr )
{
    UINT32 retVal = (UINT32)((CLR_RT_HeapBlock *)param0)->DataType();
    return retVal;
}


