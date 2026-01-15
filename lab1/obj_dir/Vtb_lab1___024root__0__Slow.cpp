// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_lab1.h for the primary calling header

#include "Vtb_lab1__pch.h"

VL_ATTR_COLD void Vtb_lab1___024root___eval_static(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_static\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lab1__DOT__clk50__0 
        = vlSelfRef.tb_lab1__DOT__clk50;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lab1__DOT__uut__DOT__clk1__0 
        = vlSelfRef.tb_lab1__DOT__uut__DOT__clk1;
}

VL_ATTR_COLD void Vtb_lab1___024root___eval_initial__TOP(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_initial__TOP\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0U] = 0x3fU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[1U] = 6U;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[2U] = 0x5bU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[3U] = 0x4fU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[4U] = 0x66U;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[5U] = 0x6dU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[6U] = 0x7dU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[7U] = 7U;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[8U] = 0x7fU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[9U] = 0x6fU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0x0000000aU] = 0x77U;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0x0000000bU] = 0x7cU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0x0000000cU] = 0x39U;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0x0000000dU] = 0x5eU;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0x0000000eU] = 0x79U;
    vlSelfRef.tb_lab1__DOT__uut__DOT__decoder7[0x0000000fU] = 0x71U;
    vlSymsp->_vm_contextp__->dumpfile("waveform.vcd"s);
    vlSymsp->_traceDumpOpen();
}

VL_ATTR_COLD void Vtb_lab1___024root___eval_final(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_final\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_lab1___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_lab1___024root___eval_phase__stl(Vtb_lab1___024root* vlSelf);

VL_ATTR_COLD void Vtb_lab1___024root___eval_settle(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_settle\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_lab1___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("sim/lab1_tb.sv", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vtb_lab1___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vtb_lab1___024root___eval_triggers__stl(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_triggers__stl\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_lab1___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vtb_lab1___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_lab1___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_lab1___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_lab1___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<CData/*0:0*/, 16> Vtb_lab1__ConstPool__TABLE_h0ab47db4_0;

VL_ATTR_COLD void Vtb_lab1___024root___stl_sequent__TOP__0(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___stl_sequent__TOP__0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = vlSelfRef.tb_lab1__DOT__uut__DOT__state;
    vlSelfRef.tb_lab1__DOT__uut__DOT__enable = Vtb_lab1__ConstPool__TABLE_h0ab47db4_0
        [__Vtableidx1];
}

VL_ATTR_COLD void Vtb_lab1___024root____Vm_traceActivitySetAll(Vtb_lab1___024root* vlSelf);

VL_ATTR_COLD void Vtb_lab1___024root___eval_stl(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_stl\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_lab1___024root___stl_sequent__TOP__0(vlSelf);
        Vtb_lab1___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_lab1___024root___eval_phase__stl(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_phase__stl\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_lab1___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vtb_lab1___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_lab1___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_lab1___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_lab1___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_lab1___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_lab1.clk50)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge tb_lab1.uut.clk1)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_lab1___024root____Vm_traceActivitySetAll(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root____Vm_traceActivitySetAll\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
}

VL_ATTR_COLD void Vtb_lab1___024root___ctor_var_reset(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___ctor_var_reset\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_lab1__DOT__clk50 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3478228656191292528ull);
    vlSelf->tb_lab1__DOT__enc1a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16083021979917465572ull);
    vlSelf->tb_lab1__DOT__enc1b = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14684109524916956108ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_lab1__DOT__uut__DOT__decoder7[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3293839026794422850ull);
    }
    vlSelf->tb_lab1__DOT__uut__DOT__clk_count = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 199740971396315126ull);
    vlSelf->tb_lab1__DOT__uut__DOT__clk1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13179437295450518135ull);
    vlSelf->tb_lab1__DOT__uut__DOT__counter = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 71241692607494872ull);
    vlSelf->tb_lab1__DOT__uut__DOT__state = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16210805485431952171ull);
    vlSelf->tb_lab1__DOT__uut__DOT__enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8860597449485963871ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_lab1__DOT__clk50__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_lab1__DOT__uut__DOT__clk1__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
