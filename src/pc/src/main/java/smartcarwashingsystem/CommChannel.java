package smartcarwashingsystem;

/**
 * Simple interface for an async msg communication channel.
 */
public interface CommChannel {

    /**
     * Sends a message represented by a string (without new line) in async way.
     * @param msg the message.
     */
    void sendMsg(String msg);

    /**
     * Receives a message with blocking behavior.
     * @return the message.
     */
    String receiveMsg();

    /**
     * Checks if a message is available.
     * @return the result.
     */
    boolean isMsgAvailable();

    /**
     * Closes the port on which the communication was established.
    */
    void closePort();

}
