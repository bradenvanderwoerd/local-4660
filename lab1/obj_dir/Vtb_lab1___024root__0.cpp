// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_lab1.h for the primary calling header

#include "Vtb_lab1__pch.h"

VL_ATTR_COLD void Vtb_lab1___024root___eval_initial__TOP(Vtb_lab1___024root* vlSelf);
VlCoroutine Vtb_lab1___024root___eval_initial__TOP__Vtiming__0(Vtb_lab1___024root* vlSelf);
VlCoroutine Vtb_lab1___024root___eval_initial__TOP__Vtiming__1(Vtb_lab1___024root* vlSelf);

void Vtb_lab1___024root___eval_initial(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_initial\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_lab1___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vtb_lab1___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_lab1___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vtb_lab1___024root___eval_initial__TOP__Vtiming__0(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lab1__DOT__clk50 = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                             nullptr, 
                                             "sim/lab1_tb.sv", 
                                             26);
        vlSelfRef.tb_lab1__DOT__clk50 = (1U & (~ (IData)(vlSelfRef.tb_lab1__DOT__clk50)));
    }
    co_return;}

VlCoroutine Vtb_lab1___024root___eval_initial__TOP__Vtiming__1(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    VL_WRITEF_NX("Starting Simulation...\n",0);
    co_await vlSelfRef.__VdlySched.delay(0x00000000001e8480ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         106);
    VL_WRITEF_NX("\n--- Testing Clockwise Rotation ---\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         45);
    VL_WRITEF_NX("  -> CW Step 1: 01\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 0U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         50);
    VL_WRITEF_NX("  -> CW Step 2: 00\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 0U;
    vlSelfRef.tb_lab1__DOT__enc1b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         55);
    VL_WRITEF_NX("  -> CW Step 3: 10\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         60);
    VL_WRITEF_NX("  -> CW Step 4: 11 (Detent Completed)\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         65);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         45);
    VL_WRITEF_NX("  -> CW Step 1: 01\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 0U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         50);
    VL_WRITEF_NX("  -> CW Step 2: 00\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 0U;
    vlSelfRef.tb_lab1__DOT__enc1b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         55);
    VL_WRITEF_NX("  -> CW Step 3: 10\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         60);
    VL_WRITEF_NX("  -> CW Step 4: 11 (Detent Completed)\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         65);
    VL_WRITEF_NX("Check: Digit 0 is ENABLED (ct[0] is low).\n\n--- Testing Counter-Clockwise Rotation ---\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         74);
    VL_WRITEF_NX("  -> CCW Step 1: 10\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         79);
    VL_WRITEF_NX("  -> CCW Step 2: 00\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 0U;
    vlSelfRef.tb_lab1__DOT__enc1b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         84);
    VL_WRITEF_NX("  -> CCW Step 3: 01\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 0U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         89);
    VL_WRITEF_NX("  -> CCW Step 4: 11 (Detent Completed)\n",0);
    vlSelfRef.tb_lab1__DOT__enc1a = 1U;
    vlSelfRef.tb_lab1__DOT__enc1b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000016e360ULL, 
                                         nullptr, "sim/lab1_tb.sv", 
                                         94);
    VL_WRITEF_NX("\nSimulation Complete.\n",0);
    VL_STOP_MT("sim/lab1_tb.sv", 124, "");
    co_return;}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_lab1___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vtb_lab1___024root___eval_triggers__act(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_triggers__act\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__clk1) 
                                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_lab1__DOT__uut__DOT__clk1__0))) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_lab1__DOT__clk50) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_lab1__DOT__clk50__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lab1__DOT__clk50__0 
        = vlSelfRef.tb_lab1__DOT__clk50;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lab1__DOT__uut__DOT__clk1__0 
        = vlSelfRef.tb_lab1__DOT__uut__DOT__clk1;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_lab1___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vtb_lab1___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___trigger_anySet__act\n"); );
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

void Vtb_lab1___024root___nba_sequent__TOP__0(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___nba_sequent__TOP__0\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vdly__tb_lab1__DOT__uut__DOT__clk_count;
    __Vdly__tb_lab1__DOT__uut__DOT__clk_count = 0;
    // Body
    __Vdly__tb_lab1__DOT__uut__DOT__clk_count = vlSelfRef.tb_lab1__DOT__uut__DOT__clk_count;
    if ((0U == (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__clk_count))) {
        __Vdly__tb_lab1__DOT__uut__DOT__clk_count = 0x000061a7U;
        vlSelfRef.tb_lab1__DOT__uut__DOT__clk1 = (1U 
                                                  & (~ (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__clk1)));
    } else {
        __Vdly__tb_lab1__DOT__uut__DOT__clk_count = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__clk_count) 
                            - (IData)(1U)));
        vlSelfRef.tb_lab1__DOT__uut__DOT__clk1 = (1U 
                                                  & (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__clk1));
    }
    vlSelfRef.tb_lab1__DOT__uut__DOT__clk_count = __Vdly__tb_lab1__DOT__uut__DOT__clk_count;
}

extern const VlUnpacked<CData/*0:0*/, 16> Vtb_lab1__ConstPool__TABLE_h0ab47db4_0;

void Vtb_lab1___024root___nba_sequent__TOP__1(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___nba_sequent__TOP__1\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.tb_lab1__DOT__uut__DOT__counter = (0x0000003fU 
                                                 & ((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__enable)
                                                     ? 
                                                    (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__enable) 
                                                      & ((~ 
                                                          (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                                            >> 3U) 
                                                           | (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state))) 
                                                         | (((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                                             >> 3U) 
                                                            & (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state))))
                                                      ? 
                                                     ((IData)(1U) 
                                                      + (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__counter))
                                                      : 
                                                     ((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__counter) 
                                                      - (IData)(1U)))
                                                     : (IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__counter)));
    vlSelfRef.tb_lab1__DOT__uut__DOT__state = ((0x0000000cU 
                                                & ((IData)(vlSelfRef.tb_lab1__DOT__uut__DOT__state) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.tb_lab1__DOT__enc1a) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.tb_lab1__DOT__enc1b)));
    __Vtableidx1 = vlSelfRef.tb_lab1__DOT__uut__DOT__state;
    vlSelfRef.tb_lab1__DOT__uut__DOT__enable = Vtb_lab1__ConstPool__TABLE_h0ab47db4_0
        [__Vtableidx1];
}

void Vtb_lab1___024root___eval_nba(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_nba\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_lab1___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_lab1___024root___nba_sequent__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
}

void Vtb_lab1___024root___timing_resume(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___timing_resume\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_lab1___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_lab1___024root___eval_phase__act(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_phase__act\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_lab1___024root___eval_triggers__act(vlSelf);
    Vtb_lab1___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_lab1___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vtb_lab1___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

void Vtb_lab1___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_lab1___024root___eval_phase__nba(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_phase__nba\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_lab1___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_lab1___024root___eval_nba(vlSelf);
        Vtb_lab1___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_lab1___024root___eval(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_lab1___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("sim/lab1_tb.sv", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtb_lab1___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("sim/lab1_tb.sv", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vtb_lab1___024root___eval_phase__act(vlSelf));
    } while (Vtb_lab1___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vtb_lab1___024root___eval_debug_assertions(Vtb_lab1___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lab1___024root___eval_debug_assertions\n"); );
    Vtb_lab1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
