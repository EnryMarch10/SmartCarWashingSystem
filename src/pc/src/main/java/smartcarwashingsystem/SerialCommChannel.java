package smartcarwashingsystem;

import java.util.Objects;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;

/**
 * CommChannel implementation based on serial port.
 */
@SuppressWarnings("PMD.AvoidStringBufferField")
public class SerialCommChannel implements CommChannel, SerialPortEventListener {

    private final SerialPort serialPort;
    private final BlockingQueue<String> queue;
    private StringBuffer currentMsg;

    /**
     * Constructor.
     * @param port the port number.
     * @param rate the baud rate.
     * @throws Exception a general exception.
     */
    @SuppressFBWarnings(value = "MC_OVERRIDABLE_METHOD_CALL_IN_CONSTRUCTOR", justification = "I know what I'm doing")
    public SerialCommChannel(final String port, final int rate) throws Exception { // NOPMD
        queue = new ArrayBlockingQueue<>(100);
        currentMsg = new StringBuffer("");
        serialPort = new SerialPort(port);

        try {
            serialPort.openPort();
            serialPort.setParams(rate, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
            serialPort.addEventListener(this);
            // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
        } catch (final SerialPortException e) {
            System.err.println(e.getMessage()); // NOPMD
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void sendMsg(final String msg) {
        final char[] array = (msg + "\n").toCharArray();
        final byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch (final SerialPortException e) {
            System.err.println(e.getMessage()); // NOPMD
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String receiveMsg() {
        String result = null;
        try {
            result = queue.take();
        } catch (final InterruptedException e) {
            System.err.println(e.getMessage()); // NOPMD
        }
        return result;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    /**
     * This should be called when you stop using the port.
     * This will prevent port locking on platforms like Linux.
     */
    @Override
    public void closePort() {
        try {
            if (!Objects.isNull(serialPort)) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (final SerialPortException e) {
            System.err.println(e.getMessage()); // NOPMD
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void serialEvent(final SerialPortEvent event) {
        /* if there are bytes received in the input buffer */
        if (event.isRXCHAR()) {
            try {
                    final String msg = serialPort.readString(event.getEventValue())
                        .replaceAll("\r", "");
                    currentMsg.append(msg);
                    boolean goAhead = true;
                    while (goAhead) {
                        final String msg2 = currentMsg.toString();
                        final int index = msg2.indexOf('\n');
                        if (index >= 0) {
                            queue.put(msg2.substring(0, index));
                            currentMsg = new StringBuffer("");
                            if (index + 1 < msg2.length()) {
                                currentMsg.append(msg2.substring(index + 1));
                            }
                        } else {
                            goAhead = false;
                        }
                    }
            } catch (final SerialPortException | InterruptedException | ClassCastException e) {
                System.err.println(e.getMessage()); // NOPMD
            }
        }
    }
}
