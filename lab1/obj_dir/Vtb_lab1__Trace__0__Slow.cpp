// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtb_lab1__Syms.h"


VL_ATTR_COLD void Vtb_lab1___024root__trace_init_sub__TOP__0(Vtb_lab1___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_init_sub__TOP__0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("tb_lab1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+21,0,"clk50",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"enc1a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"enc1b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+24,0,"leds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+27,0,"ct",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->pushPrefix("uut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+21,0,"clk50",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+24,0,"leds",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+27,0,"ct",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+22,0,"enc1a",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"enc1b",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("decoder7", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+1+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 7,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+25,0,"clk_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+26,0,"clk1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"counter",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+18,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+19,0,"enable",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+20,0,"up",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_lab1___024root__trace_init_top(Vtb_lab1___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_init_top\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_lab1___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtb_lab1___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtb_lab1___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtb_lab1___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtb_lab1___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtb_lab1___024root__trace_register(Vtb_lab1___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_register\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtb_lab1___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtb_lab1___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtb_lab1___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtb_lab1___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtb_lab1___024root__trace_const_0_sub_0(Vtb_lab1___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtb_lab1___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_const_0\n"); );
    // Body
    Vtb_lab1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_lab1___024root*>(voidSelf);
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_lab1___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_lab1___024root__trace_const_0_sub_0(Vtb_lab1___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_const_0_sub_0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullCData(oldp+27,(0x0eU),4);
}

VL_ATTR_COLD void Vtb_lab1___024root__trace_full_0_sub_0(Vtb_lab1___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtb_lab1___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_full_0\n"); );
    // Body
    Vtb_lab1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_lab1___024root*>(voidSelf);
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_lab1___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_lab1___024root__trace_full_0_sub_0(Vtb_lab1___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root__trace_full_0_sub_0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullCData(oldp+1,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0]),8);
    bufp->fullCData(oldp+2,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[1]),8);
    bufp->fullCData(oldp+3,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[2]),8);
    bufp->fullCData(oldp+4,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[3]),8);
    bufp->fullCData(oldp+5,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[4]),8);
    bufp->fullCData(oldp+6,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[5]),8);
    bufp->fullCData(oldp+7,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[6]),8);
    bufp->fullCData(oldp+8,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[7]),8);
    bufp->fullCData(oldp+9,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[8]),8);
    bufp->fullCData(oldp+10,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[9]),8);
    bufp->fullCData(oldp+11,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[10]),8);
    bufp->fullCData(oldp+12,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[11]),8);
    bufp->fullCData(oldp+13,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[12]),8);
    bufp->fullCData(oldp+14,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[13]),8);
    bufp->fullCData(oldp+15,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[14]),8);
    bufp->fullCData(oldp+16,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[15]),8);
    bufp->fullCData(oldp+17,(vlSelfRef.tb_lab1__DOT__uut__DOT__counter),6);
    bufp->fullCData(oldp+18,(vlSelfRef.tb_lab1__DOT__uut__DOT__state),4);
    bufp->fullBit(oldp+19,(vlSelfRef.tb_lab1__DOT__uut__DOT__enable));
    bufp->fullBit(oldp+20,(((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__enable) 
                            & ((~ (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                    >> 3U) | (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state))) 
                               | (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                   >> 3U) & (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state))))));
    bufp->fullBit(oldp+21,(vlSelfRef.tb_lab1__DOT__clk50));
    bufp->fullBit(oldp+22,(vlSelfRef.tb_lab1__DOT__enc1a));
    bufp->fullBit(oldp+23,(vlSelfRef.tb_lab1__DOT__enc1b));
    bufp->fullCData(oldp+24,(vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7
                             [(0x0000000fU & ((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__counter) 
                                              >> 2U))]),8);
    bufp->fullSData(oldp+25,(vlSelfRef.tb_lab1__DOT__uut__DOT__clk_count),16);
    bufp->fullBit(oldp+26,(vlSelfRef.tb_lab1__DOT__uut__DOT__clk1));
}
