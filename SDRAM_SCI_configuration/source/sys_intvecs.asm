;-------------------------------------------------------------------------------
; sys_intvecs.asm
;
; Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com 
; 
; 
;  Redistribution and use in source and binary forms, with or without 
;  modification, are permitted provided that the following conditions 
;  are met:
;
;    Redistributions of source code must retain the above copyright 
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the 
;    documentation and/or other materials provided with the   
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;
;

    .sect ".intvecs"
    .arm

;-------------------------------------------------------------------------------
; import reference for interrupt routines

    .ref _c_int00
    .ref _dabort

    .def resetEntry

;-------------------------------------------------------------------------------
; interrupt vectors
;
; the vectors are served by branch instructions which
; transfer execution to addresses specified by corresponding
; word at address offset by 0x60 to the instruction.
; This setup allows to overlay addresses 0x40 to 0x5f
; by Parameter Overlay Module (POM) when application
; is started

resetEntry
        b   _c_int00         ; 0x00
        ldr pc,[pc,#0x58]    ; 0x04 undefined
        ldr pc,[pc,#0x58]    ; 0x08 SVC
        ldr pc,[pc,#0x58]    ; 0x0C prefetch abort
        ldr pc,[pc,#0x58]    ; 0x10 data abort
        ldr pc,[pc,#0x58]    ; 0x14 reserved
        ldr pc,[pc,#0x58]    ; 0x18 IRQ
        ldr pc,[pc,#0x58]    ; 0x1C FIQ
; Above instructions are coded as 0xe59ff058

; Initial content and processing of exceptions
; used by startup code

        b   _c_int00         ; 0x20
undefEntry
        b   undefEntry       ; 0x24
svcEntry
        b   svcEntry         ; 0x28
prefetchEntry
        b   prefetchEntry    ; 0x2C
b_to_dabort
        b   _dabort          ; 0x30
reservedEntry
        b   reservedEntry    ; 0x34
b_to_IRQVECREG
        ldr pc,[pc,#-0x1d0]  ; 0x38 -> FFFFFE70h IRQVECREG
b_to_FIQVECREG
        ldr pc,[pc,#-0x1d0]  ; 0x3C -> FFFFFE74h FIQVECREG

; Space from 0x40 to 0x5f is reserved to align target address
; entries to location where is would be in 64 byte POM block
; if standard sequence with
;       ldr pc,[pc,#0x18]
; is used

        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]
        ldr pc,[pc,#0x18]

; Area with target addresses of exception processing
; routines

        .long _c_int00       ; 0x60
        .long undefEntry     ; 0x64
        .long svcEntry       ; 0x68
        .long prefetchEntry  ; 0x6C
        .long b_to_dabort    ; 0x70
        .long reservedEntry  ; 0x74
        .long b_to_IRQVECREG ; 0x78
        .long b_to_FIQVECREG ; 0x7C

;-------------------------------------------------------------------------------
