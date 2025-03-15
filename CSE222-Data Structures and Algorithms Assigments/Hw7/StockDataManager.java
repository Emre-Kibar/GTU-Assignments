/**
 * StockDataManager manages stock data using an AVL tree for efficient 
 * insertion, deletion, and searching operations. It supports adding,
 * updating, removing, and searching for stocks.
 */
public class StockDataManager{
    private AVLTree avlTree;

    /**
     * Constructs a new StockDataManager and initializes the AVL tree.
     */
    public StockDataManager(){
        avlTree = new AVLTree();
    }

    /**
     * Adds a new stock to the AVL tree or updates an existing stock's details if it already exists.
     * @param symbol the symbol of the stock
     * @param price the price of the stock
     * @param volume the trading volume of the stock
     * @param marketCap the market capitalization of the stock
     */
    public void addOrUpdateStock(String symbol, double price, long volume, long marketCap){
        // Search for the existing stock
        Stock existingStock = avlTree.search(symbol);
        if(existingStock != null){
            // Update the existing stock's details
            existingStock.setPrice(price);
            existingStock.setVolume(volume);
            existingStock.setMarketCap(marketCap);
        }else{
            // Create a new stock and insert it into the AVL tree
            Stock newStock = new Stock(symbol, price, volume, marketCap);
            avlTree.insert(newStock);
        }
    }

    /**
     * Removes a stock with the specified symbol from the AVL tree.
     * @param symbol the symbol of the stock to be removed
     */
    public void removeStock(String symbol){
        avlTree.delete(symbol);
    }

    /**
     * Searches for a stock with the specified symbol in the AVL tree.
     * @param symbol the symbol of the stock to be searched for
     * @return the stock with the specified symbol, or null if not found
     */
    public Stock searchStock(String symbol){
        return avlTree.search(symbol);
    }

    /**
     * Updates the details of an existing stock.
     * @param symbol the symbol of the stock to be updated
     * @param newPrice the new price of the stock
     * @param newVolume the new trading volume of the stock
     * @param newMarketCap the new market capitalization of the stock
     */
    public void updateStock(String symbol, double newPrice, long newVolume, long newMarketCap){
        //Search for the existing stock
        Stock stock = avlTree.search(symbol);
        if(stock != null){
            //Update the stock's details
            stock.setPrice(newPrice);
            stock.setVolume(newVolume);
            stock.setMarketCap(newMarketCap);
        }
    }
}
