// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_lab1.h for the primary calling header

#ifndef VERILATED_VTB_LAB1___024ROOT_H_
#define VERILATED_VTB_LAB1___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_lab1__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_lab1___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_lab1__DOT__clk50;
    CData/*0:0*/ tb_lab1__DOT__enc1a;
    CData/*0:0*/ tb_lab1__DOT__enc1b;
    CData/*0:0*/ tb_lab1__DOT__uut__DOT__clk1;
    CData/*5:0*/ tb_lab1__DOT__uut__DOT__counter;
    CData/*3:0*/ tb_lab1__DOT__uut__DOT__state;
    CData/*0:0*/ tb_lab1__DOT__uut__DOT__enable;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_lab1__DOT__clk50__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_lab1__DOT__uut__DOT__clk1__0;
    SData/*15:0*/ tb_lab1__DOT__uut__DOT__clk_count;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*7:0*/, 16> tb_lab1__DOT__uut__DOT__decoder7;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vtb_lab1__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_lab1___024root(Vtb_lab1__Syms* symsp, const char* namep);
    ~Vtb_lab1___024root();
    VL_UNCOPYABLE(Vtb_lab1___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
