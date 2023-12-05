package smartcarwashingsystem;

import java.io.BufferedReader;
import java.io.Console;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

/**
* Testing simple message passing.
*/
public final class TestReceiver {

    private static final String ARDUINO_MESSAGE_PREFIX = "log> ";
    private static final String MAINTENANCE_REQUEST = "Maintenance Required";
    private static final String MAINTENANCE_DONE = "Maintenance done";


    private static final int DEFAULT_BAUD_RATE = 9600;
    private static final String INFO = "only accepted 1: [port] or 2: [port] [baud rate] arguments";
    private static final int SLEEP1 = 4000;
    private static final int SLEEP2 = 500;

    private TestReceiver() { }

    /**
    * Main of the program.
    * @param args cmd args.
    * @throws Exception the exception.
    */
    @SuppressWarnings("PMD.AssignmentInOperand")
    public static void main(final String[] args) throws Exception { // NOPMD
        int baudRate = DEFAULT_BAUD_RATE;
        String port = null;

        if (args.length == 1) {
            port = args[0];
        } else if (args.length == 2) {
            port = args[0];
            try {
                baudRate = Integer.parseInt(args[1]);
            } catch (final NumberFormatException e) {
                System.err.println("Non numeric baud rate, " + INFO); // NOPMD
                System.exit(-1);
            }
        } else if (args.length > 2) {
            System.err.println("Invalid format, " + INFO); // NOPMD
            System.exit(-1);
        } else {
            String out;
            String err;
            try {
                final Process process = Runtime.getRuntime()
                    .exec("python " + new File("src/main/resources/arduinoportfinder.py").getAbsolutePath());
                try (BufferedReader stdout = new BufferedReader(new InputStreamReader(process.getInputStream(),
                        StandardCharsets.UTF_8))) {
                    while ((out = stdout.readLine()) != null) {
                        port = out;
                    }
                }
                try (BufferedReader stderr = new BufferedReader(new InputStreamReader(process.getErrorStream(),
                        StandardCharsets.UTF_8))) {
                    while ((err = stderr.readLine()) != null) {
                        System.err.println(err); // NOPMD
                    }
                }
            } catch (final IOException e) {
                System.err.println(e.getMessage()); // NOPMD
                System.exit(-1);
            }
        }

        if (Objects.isNull(port)) {
            System.err.println("Arduino Uno not connected to a serial port, " + INFO); // NOPMD
            System.exit(-1);
        }

        final CommChannel channel = new SerialCommChannel(port, baudRate);

        final Console console = System.console();

        console.printf("Waiting Arduino for rebooting..." + System.lineSeparator());
        Thread.sleep(SLEEP1);
        console.printf("Ready" + System.lineSeparator());

        boolean maintenance = false;
        while (true) {
            final String msg = channel.receiveMsg();
            if (maintenance) {
                String answer;
                do {
                    answer = console.readLine("write \"" + MAINTENANCE_DONE + "\" to go on: ");
                } while (!MAINTENANCE_DONE.equals(answer));
                channel.sendMsg(MAINTENANCE_DONE);
                maintenance = false;
            } else {
                if (msg.startsWith(ARDUINO_MESSAGE_PREFIX)) {
                    if (MAINTENANCE_REQUEST.equals(msg.substring(ARDUINO_MESSAGE_PREFIX.length()))) {
                        maintenance = true;
                        console.printf("ACCEPTED => " + msg + System.lineSeparator());
                    } else if (msg.contains("washes =")) {
                        final String[] msgT = msg.split("=");
                        if (msgT.length != 2) {
                            System.err.println("Error in arduino washes string format, string was \"" + msg + "\""); // NOPMD
                            System.exit(-1);
                        }
                        int washes = 0;
                        try {
                            washes = Integer.parseInt(msgT[1]);
                        } catch (final NumberFormatException e) {
                            System.err.println("Non numeric baud rate, " + INFO); // NOPMD
                            System.exit(-1);
                        }
                        console.printf("ACCEPTED => washes = " + washes + System.lineSeparator());
                    } else if (msg.contains("temperature =")) {
                        final String[] msgT = msg.split("=");
                        if (msgT.length != 2) {
                            System.err.println("Error in arduino temperature string format, string was \"" + msg + "\""); // NOPMD
                            System.exit(-1);
                        }
                        float temperature = Float.MIN_VALUE;
                        try {
                            temperature = Float.parseFloat(msgT[1]);
                        } catch (final NumberFormatException e) {
                            System.err.println("Non numeric baud rate, " + INFO); // NOPMD
                            System.exit(-1);
                        }
                        console.printf("ACCEPTED => T = " + temperature + "/C" + System.lineSeparator());
                    }
                } else {
                    console.printf("IGNORED => " + msg + System.lineSeparator());
                }
            }
            Thread.sleep(SLEEP2);
        }
    }

}
