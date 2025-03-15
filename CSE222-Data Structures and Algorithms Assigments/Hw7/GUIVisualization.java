import javax.swing.*;
import java.awt.*;
import java.util.Arrays;
import java.util.List;

/**
 * GUIVisualization is a JFrame-based class for visualizing performance graphs.
 * It supports both line and scatter plot types.
 */
public class GUIVisualization extends JFrame {
    private List<Integer> dataPointsX; // List to store x-axis data points
    private List<Long> dataPointsY; // List to store y-axis data points
    private String plotType; // Type of plot ("line" or "scatter")
    private double xScale; // Scaling factor for x-axis
    private double yScale; // Scaling factor for y-axis

    /**
     * Constructor for GUIVisualization.
     * @param plotType     The type of plot ("line" or "scatter").
     * @param initialSizes Array of integers representing the initial sizes for the x-axis.
     * @param timeValues   List of Long values representing the time values for the y-axis.
     * @param operationName The name of the operation to be displayed in the title.
     */
    public GUIVisualization(String plotType, Integer[] initialSizes, List<Long> timeValues, String operationName){
        this.plotType = plotType; // Set the plot type
        this.dataPointsX = Arrays.asList(initialSizes); // Initialize x-axis data points array
        this.dataPointsY = timeValues; // Initialize y-axis data points list

        setTitle("Performance Graph Visualization: " + operationName); // Set the title of the window
        setSize(800, 600); // Set the size of the window
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Set the default close operation
        setLocationRelativeTo(null); // Center the window on the screen

        xScale = 1; // Initialize x-axis scaling factor
        yScale = 1; // Initialize y-axis scaling factor
    }

    /**
     * Overridden paint method to draw the graph.
     *
     * @param g The Graphics object to protect.
     */
    @Override
    public void paint(Graphics g){
        super.paint(g); // Call the superclass's paint method
        drawGraph(g); // Draw the graph
    }

    /**
     * Method to draw the graph on the given Graphics object.
     *
     * @param g The Graphics object to draw on.
     */
    private void drawGraph(Graphics g){
        int width = getWidth(); // Get the width of the window
        int height = getHeight(); // Get the height of the window
        int padding = 50; // Padding around the graph
        int labelPadding = 20; // Padding for labels
        int topPadding = 50; // Additional padding for the top
    
        Graphics2D g2 = (Graphics2D) g; // Cast Graphics to Graphics2D for better rendering
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); // Enable anti-aliasing
    
        // Draw white background for the graph
        g2.setColor(Color.WHITE);
        g2.fillRect(padding + labelPadding, topPadding, width - 2 * padding - labelPadding, height - 2 * padding - labelPadding - topPadding);
        g2.setColor(Color.BLACK);
    
        // Create hatch marks and grid lines for y axis.
        int numberYDivisions = 10; // Number of divisions for the y-axis
        for(int i = 0; i < numberYDivisions + 1; i++){
            int x0 = padding + labelPadding;
            int x1 = width - padding;
            int y0 = height - ((i * (height - padding * 2 - labelPadding - topPadding)) / numberYDivisions + padding);
            int y1 = y0;
            if(dataPointsY.size() > 0){
                g2.setColor(Color.LIGHT_GRAY); // Set color for grid lines
                g2.drawLine(padding + labelPadding + 1 + labelPadding, y0, x1, y1); // Draw grid line
                g2.setColor(Color.BLACK); // Set color for labels
                String yLabel = ((int) ((getMaxYValue() * ((i * 1.0) / numberYDivisions)) * 100)) / 100.0 + ""; // Generate y-axis label
                FontMetrics metrics = g2.getFontMetrics(); // Get font metrics for label width
                int labelWidth = metrics.stringWidth(yLabel);
                g2.drawString(yLabel, x0 - labelWidth - 5, y0 + (metrics.getHeight() / 2) - 3); // Draw y-axis label
            }
        }
    
        // Create hatch marks and grid lines for x axis.
        for(int i = 0; i < dataPointsX.size(); i++){
            if(dataPointsX.size() > 1){
                int x0 = (int) (i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) * xScale) + padding + labelPadding;
                int x1 = x0;
                int y0 = height - padding - labelPadding;
                int y1 = y0 - 4;
                if((i % ((int) ((dataPointsX.size() / 20.0)) + 1)) == 0){
                    g2.setColor(Color.LIGHT_GRAY); // Set color for grid lines
                    g2.drawLine(x0, height - padding - labelPadding - 1 - labelPadding, x1, topPadding); // Draw grid line
                    g2.setColor(Color.BLACK); // Set color for labels
                    String xLabel = dataPointsX.get(i) + ""; // Generate x-axis label
                    FontMetrics metrics = g2.getFontMetrics(); // Get font metrics for label width
                    int labelWidth = metrics.stringWidth(xLabel);
                    g2.drawString(xLabel, x0 - labelWidth / 2, y0 + metrics.getHeight() + 3); // Draw x-axis label
                }
                g2.drawLine(x0, y0, x1, y1); // Draw x-axis hatch mark
            }
        }
    
        // Draw axis lines.
        g2.drawLine(padding + labelPadding, height - padding - labelPadding, padding + labelPadding, topPadding); // y-axis
        g2.drawLine(padding + labelPadding, height - padding - labelPadding, width - padding, height - padding - labelPadding); // x-axis
    
        // Draw the actual graph.
        Stroke oldStroke = g2.getStroke();
        g2.setColor(Color.BLUE); // Set color for the graph
        g2.setStroke(new BasicStroke(2f)); // Set stroke for the graph
    
        if (plotType.equals("line")) {
            for (int i = 0; i < dataPointsX.size() - 1; i++) {
                int x1 = (int) (i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) * xScale) + padding + labelPadding;
                int y1 = height - padding - labelPadding - (int) ((dataPointsY.get(i) * 1.0) / getMaxYValue() * (height - padding * 2 - labelPadding - topPadding) * yScale);
                int x2 = (int) ((i + 1) * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) * xScale) + padding + labelPadding;
                int y2 = height - padding - labelPadding - (int) ((dataPointsY.get(i + 1) * 1.0) / getMaxYValue() * (height - padding * 2 - labelPadding - topPadding) * yScale);
                g2.drawLine(x1, y1, x2, y2); // Draw line between data points
            }
        } else if (plotType.equals("scatter")) {
            for (int i = 0; i < dataPointsX.size(); i++) {
                int x = (int) (i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) * xScale) + padding + labelPadding;
                int y = height - padding - labelPadding - (int) ((dataPointsY.get(i) * 1.0) / getMaxYValue() * (height - padding * 2 - labelPadding - topPadding) * yScale);
                g2.fillOval(x - 3, y - 3, 6, 6); // Draw data point as a small circle
            }
        }
    
        g2.setStroke(oldStroke); // Restore original stroke
    }

    /**
     * Method to get the maximum y-value from the data points.
     * @return The maximum y-value.
     */
    private long getMaxYValue(){
        long max = Long.MIN_VALUE; //Initialize max value to minimum possible value
        for (Long y : dataPointsY) {
            max = Math.max(max, y); //Find maximum y value
        }
        return max; // Return maximum y value
    }
}
