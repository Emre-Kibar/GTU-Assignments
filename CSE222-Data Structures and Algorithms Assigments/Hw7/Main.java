import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javax.swing.SwingUtilities;

/**
 * Main class to perform operations on stock data and visualize the performance.
 */
public class Main {
    // INITIALSIZES gives the xAxis of graphs and yAxis for each operation is held inside the Lists.
    private static final Random random = new Random();
    private static final Integer[] INITIAL_SIZES = {10, 500, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000};
    private static final int NUM_OPERATIONS = 100;
    private static final List<Long> addTimes = new ArrayList<>();
    private static final List<Long> removeTimes = new ArrayList<>();
    private static final List<Long> searchTimes = new ArrayList<>();
    private static final List<Long> updateTimes = new ArrayList<>();
    private static final String FILENAME = "inputFile.txt";
    private static int lastReadLine = 0; // Tracks the last read line

    /**
     * Main method to run the performance analysis and visualization.
     * @param args Command line arguments.
     */
    public static void main(String[] args){
        try{
            System.out.println("The compilation takes some time due to using -Xint command to eliminate Java optimization to take better graphs");
            System.out.println("The outputs from search commands is commented out to make compilation faster.");
            clearInputFile(); // Clear the "inputFile.txt" for new sample.
            int previousSize = 0;
            // For different initial node size program continues.
            for(int size : INITIAL_SIZES){
                generateMixedOperations(size - previousSize); // The command to create inputFile with initialNodes and random commands.
                StockDataManager manager = new StockDataManager(); // To create AVLTree a StockDataManager object is created.
                readFileAndInitializeTree(manager); // Reads the inputFile to create AVLTree.
                performPerformanceAnalysis(manager, size); // Performs analysis for operations on AVLTree.
                previousSize = size; 
            }
        }catch (IOException e){
            e.printStackTrace();
        }

        // Creates the graphs of operations.
        SwingUtilities.invokeLater(() -> {
            String plotType = "scatter";
            GUIVisualization addFrame = new GUIVisualization(plotType, INITIAL_SIZES, addTimes, "ADD Operation");
            addFrame.setVisible(true);
            GUIVisualization removeFrame = new GUIVisualization(plotType, INITIAL_SIZES, removeTimes, "REMOVE Operation");
            removeFrame.setVisible(true);
            GUIVisualization searchFrame = new GUIVisualization(plotType, INITIAL_SIZES, searchTimes, "SEARCH Operation");
            searchFrame.setVisible(true);
            GUIVisualization updateFrame = new GUIVisualization(plotType, INITIAL_SIZES, updateTimes, "UPDATE Operation");
            updateFrame.setVisible(true);
        });
    }

    /**
     * Clears the input file.
     * @throws IOException If an I/O error occurs.
     */
    private static void clearInputFile() throws IOException {
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(FILENAME))){
            //Opening the file in write mode will clear its contents
        }
    }

    /**
     * Generates a mixed set of operations and writes them to the input file.
     * @param targetAddCount The target number of ADD operations.
     * @throws IOException If an I/O error occurs.
     */
    private static void generateMixedOperations(int targetAddCount) throws IOException {
        // The operations for inputFile are randomly generated and the add commands will be counted for program analysis with initial nodes.
        int addCount = 0;
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(FILENAME, true))){
            while(addCount < targetAddCount){
                String operation = generateRandomOperation();
                if(operation.startsWith("ADD")){
                    addCount++;
                }
                writer.write(operation);
                writer.newLine();
            }
        }
    }

    /**
     * Generates a random operation.
     * @return A random operation string.
     */
    private static String generateRandomOperation(){
        // The randomly generated commands will be selected randomly to write inputFile.
        // The rate of add command is incremented to not create unnecessary big inputFile.
        int operationType = random.nextInt(7);
        String symbol = generateRandomSymbol();
        double price = generateRandomPrice();
        long volume = generateRandomVolume();
        long marketCap = generateRandomMarketCap();

        switch(operationType){
            case 0:
            case 1:
            case 2:
            case 3:
                return "ADD " + symbol + " " + price + " " + volume + " " + marketCap;
            case 4:
                return "REMOVE " + symbol;
            case 5:
                return "SEARCH " + symbol;
            case 6:
                return "UPDATE " + symbol + " " + price + " " + volume + " " + marketCap;
            default:
                return "ADD " + symbol + " " + price + " " + volume + " " + marketCap;
        }
    }

    /**
     * Generates a random stock symbol containing only uppercase letters.
     * @return A random stock symbol.
     */
    private static String generateRandomSymbol(){
        StringBuilder symbol = new StringBuilder(3);
        for (int i = 0; i < 3; i++) {
            char randomChar = (char) (random.nextInt(26) + 'A'); // ASCII range 'A' to 'Z'
            symbol.append(randomChar);
        }
        return symbol.toString();
    }

    /**
     * Generates a random stock price.
     * @return A random stock price.
     */
    private static double generateRandomPrice(){
        return Math.round(random.nextDouble() * 1000 * 100.0) / 100.0;
    }

    /**
     * Generates a random stock volume.
     * @return A random stock volume.
     */
    private static long generateRandomVolume(){
        return Math.abs(random.nextLong() % 1_000_000_000) + 1;
    }

    /**
     * Generates a random stock market capitalization.
     * @return A random stock market capitalization.
     */
    private static long generateRandomMarketCap(){
        return Math.abs(random.nextLong() % 1_000_000_000) + 1;
    }

    /**
     * Reads the input file and initializes the stock data tree.
     * @param manager The stock data manager.
     * @throws IOException If an I/O error occurs.
     */
    private static void readFileAndInitializeTree(StockDataManager manager) throws IOException {
        try(BufferedReader reader = new BufferedReader(new FileReader(FILENAME))){
            int currentLine = 0;
            String line;
            
            // Skip lines that have already been read
            while(currentLine < lastReadLine && reader.readLine() != null){
                currentLine++;
            }

            // Read and process the remaining lines
            while((line = reader.readLine()) != null){
                processCommand(line, manager);
                lastReadLine++;
            }
        }
    }

    /**
     * Processes a command and performs the corresponding operation on the stock data manager.
     * @param line The command line to process.
     * @param manager The stock data manager.
     */
    private static void processCommand(String line, StockDataManager manager){
        // The each command divided its parts and processed by StockDataManager methods.
        String[] tokens = line.split(" ");
        String command = tokens[0];

        switch (command) {
            case "ADD":
                manager.addOrUpdateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                break;
            case "REMOVE":
                manager.removeStock(tokens[1]);
                break;
            case "SEARCH":
                Stock stock = manager.searchStock(tokens[1]);
                if(stock != null){
                    //System.out.println(stock); //This line is commented out because printing the nodes makes slower the compilation.
                }
                break;
            case "UPDATE":
                manager.updateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                break;
            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }

    /**
     * Performs performance analysis by measuring the time taken for various operations.
     * @param manager The stock data manager.
     * @param size The size of the dataset.
     */
    public static void performPerformanceAnalysis(StockDataManager manager, int size) {
        String[] symbols = new String[NUM_OPERATIONS];
        double[] prices = new double[NUM_OPERATIONS];
        long[] volumes = new long[NUM_OPERATIONS];
        long[] marketCaps = new long[NUM_OPERATIONS];

        // Pre-generate random data
        for (int i = 0; i < NUM_OPERATIONS; i++) {
            symbols[i] = generateRandomSymbol();
            prices[i] = generateRandomPrice();
            volumes[i] = generateRandomVolume();
            marketCaps[i] = generateRandomMarketCap();
        }

        // Measure time for ADD operation
        long addTime = 0;
        for(int i = 0; i < NUM_OPERATIONS; i++){
            long startTime = System.nanoTime();
            manager.addOrUpdateStock(symbols[i], prices[i], volumes[i], marketCaps[i]);
            long endTime = System.nanoTime();
            addTime += (endTime - startTime);
        }
        addTimes.add(addTime / NUM_OPERATIONS);

        // Measure time for SEARCH operation
        long searchTime = 0;
        for(int i = 0; i < NUM_OPERATIONS; i++){
            long startTime = System.nanoTime();
            manager.searchStock(symbols[i]);
            long endTime = System.nanoTime();
            searchTime += (endTime - startTime);
        }
        searchTimes.add(searchTime / NUM_OPERATIONS);

        // Measure time for REMOVE operation
        long removeTime = 0;
        for(int i = 0; i < NUM_OPERATIONS; i++){
            long startTime = System.nanoTime();
            manager.removeStock(symbols[i]);
            long endTime = System.nanoTime();
            removeTime += (endTime - startTime);
        }
        removeTimes.add(removeTime / NUM_OPERATIONS);

        // Measure time for UPDATE operation
        long updateTime = 0;
        for(int i = 0; i < NUM_OPERATIONS; i++){
            long startTime = System.nanoTime();
            manager.updateStock(symbols[i], generateRandomPrice(), generateRandomVolume(), generateRandomMarketCap());
            long endTime = System.nanoTime();
            updateTime += (endTime - startTime);
        }
        updateTimes.add(updateTime / NUM_OPERATIONS);
    }
}
