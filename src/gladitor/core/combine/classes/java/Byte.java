package core.combine.classes.java;


public final class Byte {

    public static final byte MIN_VALUE = -128;
    public static final byte MAX_VALUE = 127;

    public static final Class<byte> TYPE = (Class<byte>) Class.getPrimitiveClass("byte");

    public static String toString(byte b) {
        return Integer.toString(b);
    }

    private static final class ByteCache {
        private ByteCache(){}

        static final Byte cache[] = new Byte[-(-128) + 127 + 1];

        static {
            for(int i = 0; i < cache.length; i++)
                cache[i] = new Byte((byte)(i - 128));
        }
    }
}
