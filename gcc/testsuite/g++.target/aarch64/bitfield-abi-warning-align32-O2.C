/* { dg-do compile } */
/* { dg-options "-O2 -save-temps -Wno-narrowing" } */

#define ALIGN 32
#define EXTRA

#include "bitfield-abi-warning.h"

/* In f1, f2, f4, f8, f16 (and stdarg versions):  */
/* { dg-final { scan-assembler-times "ldr\tx0, \\\[x1\\\]" 10 } } */

/* In fp, f1p, f2p, f4p, f8p (and stdarg versions):  */
/* { dg-final { scan-assembler-times "and\tw0, w1, 1" 10 { xfail *-*-* } } } */

/* In f16p (and stdarg version):  */
/* { dg-final { scan-assembler-times "and\tw0, w2, 1" 2 { xfail *-*-* } } } */

/* In f1_stack, f2_stack, f4_stack, f8_stack, f16_stack, f8p_stack:  */
/* { dg-final { scan-assembler-times "ldr\tx\[0-9\]+, \\\[sp, 8\\\]" 6 { xfail *-*-* } } } */

/* In fp_stack, f1p_stack:  */
/* { dg-final { scan-assembler-times "ldrb\tw0, \\\[sp, 8\\\]" 2 { xfail *-*-* } } } */

/* In f2p_stack:  */
/* { dg-final { scan-assembler-times "ldrh\tw0, \\\[sp, 8\\\]" 1 { xfail *-*-* } } } */

/* In f4p_stack:  */
/* { dg-final { scan-assembler-times "ldr\tw0, \\\[sp, 8\\\]" 1 { xfail *-*-* } } } */

/* In f16p_stack:  */
/* { dg-final { scan-assembler-times "ldr\tx0, \\\[sp, 16\\\]" 1 { xfail *-*-* } } } */

/* Bitfield parameter in registers.  */
/* No change in parameter passing in GCC 9.1 for lines 47-51 (f1, f2, f4, f8, f16)
   because the overall alignment is > 16.  No warning expected.  */

/* No change in parameter passing in GCC 9.1 for lines 53-57 (fp, f1p, f2p,
   f4p, f8p) because the argument fits in a single register.  Should not warn,
   but aarch64_function_arg_boundary would need to take the argument size into
   account as well as whether it's passed via registers or the stack.  */
/* { dg-message {parameter passing for argument of type 'Sp' changed in GCC 9.1}  "" { target *-*-* } 53 } fp */
/* { dg-message {parameter passing for argument of type 'S1p' changed in GCC 9.1} "" { target *-*-* } 54 } f1p */
/* { dg-message {parameter passing for argument of type 'S2p' changed in GCC 9.1} "" { target *-*-* } 55 } f2p */
/* { dg-message {parameter passing for argument of type 'S4p' changed in GCC 9.1} "" { target *-*-* } 56 } f4p */
/* { dg-message {parameter passing for argument of type 'S8p' changed in GCC 9.1} "" { target *-*-* } 57 } f8p */

/* Changed in GCC 9.1.  */
/* { dg-message {parameter passing for argument of type 'S16p' changed in GCC 9.1} "" { target *-*-* } 58 } f16p */


/* Bitfield call argument in registers.  */
/* No change in parameter passing in GCC 9.1 for lines 60-64 (g1, g2, g4, g8, g16)
   because the overall alignment is > 16.  No warning expected.  */

/* No change in parameter passing in GCC 9.1 for lines 66-70 (gp, g1p, g2p,
   g4p, g8p), no warning expected.  */

/* Changed in GCC 9.1, but we fail to emit a warning.  */
/* { dg-message {parameter passing for argument of type 'S16p' changed in GCC 9.1} "" { xfail *-*-* } 71 } g16p */


/* Bitfield parameter in stack.  */
/* No change in parameter passing in GCC 9.1 for lines 74-78 (f1_stack,
   f2_stack, f4_stack, f8_stack, f16_stack) because the overall alignment is >
   16.  No warning expected.  */

/* { dg-message {parameter passing for argument of type 'Sp' changed in GCC 9.1}  "" { target *-*-* } 80 } fp_stack */
/* { dg-message {parameter passing for argument of type 'S1p' changed in GCC 9.1} "" { target *-*-* } 81 } f1p_stack */
/* { dg-message {parameter passing for argument of type 'S2p' changed in GCC 9.1} "" { target *-*-* } 82 } f2p_stack */
/* { dg-message {parameter passing for argument of type 'S4p' changed in GCC 9.1} "" { target *-*-* } 83 } f4p_stack */
/* { dg-message {parameter passing for argument of type 'S8p' changed in GCC 9.1} "" { target *-*-* } 84 } f8p_stack */

/* No change in parameter passing in GCC 9.1 for line 85 (f16p_stack) because
   the overall alignment is >= 16.  No warning expected.  */

/* Bitfield call argument in stack.  */
/* No change in parameter passing in GCC 9.1 for lines 87-91 (g1_stack,
   g2_stack, g4_stack, g8_stack, g16_stack) because the overall alignment is >
   16.  No warning expected.  */

/* { dg-message {parameter passing for argument of type 'Sp' changed in GCC 9.1}  "" { target *-*-* } 93 } gp_stack */
/* { dg-message {parameter passing for argument of type 'S1p' changed in GCC 9.1} "" { target *-*-* } 94 } g1p_stack */
/* { dg-message {parameter passing for argument of type 'S2p' changed in GCC 9.1} "" { target *-*-* } 95 } g2p_stack */
/* { dg-message {parameter passing for argument of type 'S4p' changed in GCC 9.1} "" { target *-*-* } 96 } g4p_stack */
/* { dg-message {parameter passing for argument of type 'S8p' changed in GCC 9.1} "" { target *-*-* } 97 } g8p_stack */


/* No change in parameter passing in GCC 9.1 for line 98 (g16p_stack).  No
   warning expected.  */


/* Bitfield parameter in stdarg.  */
/* No change in parameter passing in GCC 9.1 for lines 101-105 (f1_stdarg,
   f2_stdarg, f4_stdarg, f8_stdarg, f16_stdarg) because the overall alignment
   is > 16.  No warning expected.  */

/* Parameter passing for these should not have changed in GCC 9.1 (PR 105549).
   Fortunately we warn. Note the discrepancy with lines 120-124 below: we warn
   in the callee, but not in the caller.  */
/* { dg-message {parameter passing for argument of type 'Sp' changed in GCC 9.1}   "" { target *-*-* } 107 } fp_stdarg */
/* { dg-message {parameter passing for argument of type 'S1p' changed in GCC 9.1}  "" { target *-*-* } 108 } f1p_stdarg */
/* { dg-message {parameter passing for argument of type 'S2p' changed in GCC 9.1}  "" { target *-*-* } 109 } f2p_stdarg */
/* { dg-message {parameter passing for argument of type 'S4p' changed in GCC 9.1}  "" { target *-*-* } 110 } f4p_stdarg */
/* { dg-message {parameter passing for argument of type 'S8p' changed in GCC 9.1}  "" { target *-*-* } 111 } f8p_stdarg */

/* No change in parameter passing in GCC 9.1 for line 112 (f16p_stdarg).
   Should not warn.  */
/* { dg-message {parameter passing for argument of type 'S16p' changed in GCC 9.1} "" { target *-*-* } 112 } f16p_stdarg */

/* Bitfield call argument in stdarg.  */
/* No change in parameter passing in GCC 9.1 for lines 114-118 (g1_stdarg,
   g2_stdarg, g4_stdarg, g8_stdarg, g16_stdarg) because the overall alignment
   is > 16.  No warning expected.  */

/* No change in parameter passing in GCC 9.1 for lines 120-124 (gp_stdarg,
   g1p_stdarg, g2p_stdarg, g4p_stdarg, g8p_stdarg), no warning expected.  */

/* Changed in GCC 9.1, but we fail to emit a warning.  */
/* { dg-message {parameter passing for argument of type 'S16p' changed in GCC 9.1} "" { xfail *-*-* } 125 } g16p_stdarg */
