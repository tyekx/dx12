#define RootSig0 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )"

#define RootSig1 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT ), CBV(b0)"

#define RootSig2 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )," \
                 "CBV(b0)," \
                 "DescriptorTable(SRV(t0, numDescriptors=1)), StaticSampler(s0)"

#define RootSig3 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )," \
                 "CBV(b0)," \
                 "CBV(b1)," \
                 "DescriptorTable(SRV(t0, numDescriptors=3)), StaticSampler(s0)"
