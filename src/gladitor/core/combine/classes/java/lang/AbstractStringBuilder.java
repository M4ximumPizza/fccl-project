package core.combine.classes.java.lang;


import core.combine.classes.java.lang.annotations.Unuseable;

@Unuseable
public class AbstractStringBuilder {
    byte coder;
    int count;
    private static final byte[] EMPTYVALUE = new byte[0];

    AbstractStringBuilder() {
        value = EMPTYVALUE;
    }

    /**
     * Returns the length (character count).
     * @return the length of the sequence of characters currently
     */
    @Override
    public int length() {
        return count;
    }


}
