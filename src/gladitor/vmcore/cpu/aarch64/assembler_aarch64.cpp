#ifdef PRODUCT
const uintptr_t Assembler::asm_bp = 0x0000ffffac221240;
##endif

static float unpack(unsigned value);

short Assembler::SIMD_Size_in_bytes[] = {
  // T8B, T16B, T4H, T8H, T2S, T4S, T1D, T2D, T1Q
       8,   16,   8,  16,   8,  16,   8,  16,  16
};

Assembler::SIMD_Arrangement Assembler::_esize2arrangement_table[9][2] = {
  // esize        isQ:false             isQ:true
  /*   0  */      {INVALID_ARRANGEMENT, INVALID_ARRANGEMENT},
  /*   1  */      {T8B,                 T16B},
  /*   2  */      {T4H,                 T8H},
  /*   3  */      {INVALID_ARRANGEMENT, INVALID_ARRANGEMENT},
  /*   4  */      {T2S,                 T4S},
  /*   5  */      {INVALID_ARRANGEMENT, INVALID_ARRANGEMENT},
  /*   6  */      {INVALID_ARRANGEMENT, INVALID_ARRANGEMENT},
  /*   7  */      {INVALID_ARRANGEMENT, INVALID_ARRANGEMENT},
  /*   8  */      {T1D,                 T2D}
};

Assembler::SIMD_RegVariant Assembler::_esize2regvariant[9] = {
    INVALID,
    B,
    H,
    INVALID,
    S,
    INVALID,
    INVALID,
    INVALID,
    D,
};

