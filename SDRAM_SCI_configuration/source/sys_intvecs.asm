;-------------------------------------------------------------------------------
; sys_intvecs.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
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
