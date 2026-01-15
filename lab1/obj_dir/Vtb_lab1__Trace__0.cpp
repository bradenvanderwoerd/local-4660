// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtb_lab1__Syms.h"


void Vtb_lab1___024root__trace_chg_0_sub_0(Vtb_lab1___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtb_lab1___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_chg_0\n"); );
    // Body
    Vtb_lab1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_lab1___024root*>(voidSelf);
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtb_lab1___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtb_lab1___024root__trace_chg_0_sub_0(Vtb_lab1___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_chg_0_sub_0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgCData(oldp+0,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0]),8);
        bufp->chgCData(oldp+1,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[1]),8);
        bufp->chgCData(oldp+2,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[2]),8);
        bufp->chgCData(oldp+3,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[3]),8);
        bufp->chgCData(oldp+4,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[4]),8);
        bufp->chgCData(oldp+5,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[5]),8);
        bufp->chgCData(oldp+6,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[6]),8);
        bufp->chgCData(oldp+7,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[7]),8);
        bufp->chgCData(oldp+8,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[8]),8);
        bufp->chgCData(oldp+9,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[9]),8);
        bufp->chgCData(oldp+10,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[10]),8);
        bufp->chgCData(oldp+11,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[11]),8);
        bufp->chgCData(oldp+12,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[12]),8);
        bufp->chgCData(oldp+13,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[13]),8);
        bufp->chgCData(oldp+14,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[14]),8);
        bufp->chgCData(oldp+15,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[15]),8);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgCData(oldp+16,(vlSelfRef.tb_lab1__DOT__uut__DOT__counter),6);
        bufp->chgCData(oldp+17,(vlSelfRef.tb_lab1__DOT__uut__DOT__state),4);
        bufp->chgBit(oldp+18,(vlSelfRef.tb_lab1__DOT__uut__DOT__enable));
        bufp->chgBit(oldp+19,(((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__enable) 
                               & ((~ (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                       >> 3U) | (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state))) 
                                  | (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                      >> 3U) & (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state))))));
    }
    bufp->chgBit(oldp+20,(vlSelfRef.tb_lab1__DOT__clk50));
    bufp->chgBit(oldp+21,(vlSelfRef.tb_lab1__DOT__enc1a));
    bufp->chgBit(oldp+22,(vlSelfRef.tb_lab1__DOT__enc1b));
    bufp->chgCData(oldp+23,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7
                            [(0x0000000fU & ((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__counter) 
                                             >> 2U))]),8);
    bufp->chgSData(oldp+24,(vlSelfRef.tb_lab1__DOT__uut__DOT__clk_count),16);
    bufp->chgBit(oldp+25,(vlSelfRef.tb_lab1__DOT__uut__DOT__clk1));
}

void Vtb_lab1___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_cleanup\n"); );
    // Body
    Vtb_lab1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_lab1___024root*>(voidSelf);
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
