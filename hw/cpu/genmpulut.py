#!/usr/bin/env python3

from typing import *


U_R = 1
U_W = 2
U_X = 4
P_R = 8
P_W =16
P_X =32

R = 1
W = 2

APLUT = [
    (0, 0),
    (R|W, 0),
    (R|W, R),
    (R|W, R|W),
    None,
    (R, 0),
    (R, R),
    #None
]


def get_apair_for_flags(flags: int) -> Tuple[int, int]:
    data = flags & (U_R|U_W | P_R|P_W)
    insn = flags & (U_X | P_X)

    insn = ((insn & U_X) >> 2) | ((insn & P_X) >> 4)
    # insn = nPX nUX ; nPX UX ; PX nUX ; PX UX
    IAPLUT = [(0,0), (R,R), (R,0), (R,R)]  # fold nPX UX to PX UX
    iap = APLUT.index(IAPLUT[insn])

    data = ((data & (U_R|U_W)) >> 0) | ((data & (P_R|P_W)) >> 1)
    # data = P-- U-- ;*P-- UR- ;*P-- U-W ;*P-- URW
    #      ; PR- U-- ; PR- UR- ;*PR- U-W ;*PR- URW
    #      ; P-W U-- ; P-W UR- ;*P-W U-W ;*P-W URW   <--- fold to PRW
    #      ; PRW U-- ; PRW UR- ; PRW U-W ; PRW URW
    #                                ^
    # entries marked with *:         |
    # P also gets U perms       fold to URW
    # => entire right half (bit 1 set) is PRW URW
    if (data & (U_R|U_W)) == U_W: data |= U_R
    if (data & (P_R|P_W)) == P_W: data |= P_R

    dap = 0
    if (data & 2): dap = (R|W,R|W)
    else:
        data = ((data & 0xfc) >> 1) | (data & 1)
        DAPLUT = [
            (0  ,0),(R  ,R),
            (R  ,0),(R  ,R),
            (R|W,0),(R|W,R),
            (R|W,0),(R|W,R),
        ]
        dap = DAPLUT[data]
    dap = APLUT.index(dap)

    return (dap, iap)


def get_flags_for_apair(dap: int, iap: int) -> int:
    flags = 0

    # insn
    if iap == 0: flags |= 0
    elif iap in (1,5): flags |= P_X
    elif iap in (2,3,6): flags |= P_X|U_X
    else: return 0 #assert False, "bad iap value 0x%x"%iap

    if dap == 0: flags |= 0
    elif dap == 1: flags |= P_R|P_W
    elif dap == 2: flags |= P_R|P_W | U_R
    elif dap == 3: flags |= P_R|P_W | U_R|U_W
    elif dap == 5: flags |= P_R
    elif dap == 6: flags |= P_R | U_R
    else: return 0 #assert False, "bad dap value 0x%x"%dap

    return flags


def str_flags(flags: int):
    r = "P"
    r += 'R' if flags & P_R else '-'
    r += 'W' if flags & P_W else '-'
    r += 'X' if flags & P_X else '-'

    r += " U"
    r += 'R' if flags & U_R else '-'
    r += 'W' if flags & U_W else '-'
    r += 'X' if flags & U_X else '-'

    return r


def str_aperm(perm: int):
    return [
        "P-- U--",
        "PRW U--",
        "PRW UR-",
        "PRW URW",
        None,
        "PR- U--",
        "PR- UR-"
    ][perm]


def main():
    print("MPU_FLAG_TO_BIT_LUT:")
    l=[0]*8
    for j in range(8):
        for i in range(8):
            dap, iap = get_apair_for_flags(i+j*8)
            l[i] = (dap << 3) | iap
            #print("%s   --->   DATA: %s   INSN: %s" % (str_flags(i), str_aperm(dap), str_aperm(iap)))
        print("\t.byte %s" % ', '.join("0x%02x"%x for x in l))

    print()
    print()

    print("MPU_BIT_TO_FLAG_LUT:")
    l=[0]*8
    for j in range(8):
        for i in range(8):
            flags = get_flags_for_apair(j, i)
            l[i] = flags
        print("\t.byte %s" % ', '.join("0x%02x"%x for x in l))


if __name__ == '__main__': main()

