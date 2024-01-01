package core.exceptions.java.lang;

/**
 * Signals that an application attempted to invoke an abstract method directly.
 * Normally, such errors are identified during compilation. However, under specific circumstances,
 * this error may manifest at runtime due to incompatible changes in class definitions
 * since the method's last compilation.
 *
 * <p>This exception is thrown when an application tries to call an abstract method directly,
 * a scenario typically detected during compilation. However, in specific instances,
 * this error may arise during runtime if there has been an incompatible modification
 * in the definition of a class since the currently executing method was last compiled.
 *
 * @since 1.0
 * @author Logan Abernathy
 */
public class AbstractMethodInvocationError extends IncompatibleClassChangeError {

    /**
     * Constructs an {@code AbstractMethodInvocationError} with no detail message.
     */
    public AbstractMethodInvocationError() {
        super();
    }

    /**
     * Constructs an {@code AbstractMethodInvocationError} with the specified detail message.
     *
     * @param message the detail message.
     */
    public AbstractMethodInvocationError(String message) {
        super(message);
    }
}
