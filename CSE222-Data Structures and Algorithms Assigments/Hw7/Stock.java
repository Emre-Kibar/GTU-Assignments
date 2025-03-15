/**
 * Represents a stock with its symbol, price, trading volume, and market capitalization.
 */
public class Stock {
    private String symbol;
    private double price;
    private long volume;
    private long marketCap;

    /**
     * Constructs a new Stock with the specified symbol, price, volume, and market capitalization.
     * @param symbol the stock symbol
     * @param price the current price of the stock
     * @param volume the current trading volume of the stock
     * @param marketCap the market capitalization of the stock
     */
    Stock(String symbol, double price, long volume, long marketCap){
        this.symbol = symbol;
        this.price = price;
        this.volume = volume;
        this.marketCap = marketCap;
    }

    /**
     * Returns the stock symbol.
     * @return the stock symbol
     */
    public String getSymbol(){
        return symbol;
    }

    /**
     * Returns the current price of the stock.
     * @return the current price of the stock
     */
    public double getPrice(){
        return price;
    }

    /**
     * Returns the current trading volume of the stock.
     * @return the current trading volume of the stock
     */
    public long getVolume(){
        return volume;
    }

    /**
     * Returns the market capitalization of the stock.
     * @return the market capitalization of the stock
     */
    public long getMarketCap(){
        return marketCap;
    }

    /**
     * Sets the stock symbol.
     * @param symbol the new stock symbol
     */
    public void setSymbol(String symbol){
        this.symbol = symbol;
    }

    /**
     * Sets the current price of the stock.
     * @param price the new price of the stock
     */
    public void setPrice(double price){
        this.price = price;
    }

    /**
     * Sets the current trading volume of the stock.
     * @param volume the new trading volume of the stock
     */
    public void setVolume(long volume){
        this.volume = volume;
    }

    /**
     * Sets the market capitalization of the stock.
     * @param marketCap the new market capitalization of the stock
     */
    public void setMarketCap(long marketCap){
        this.marketCap = marketCap;
    }

    /**
     * Returns a string representation of the stock.
     * @return a string representation of the stock
     */
    @Override
    public String toString() {
        return "Stock[" +
                "symbol:'" + symbol + '\'' +
                ", price:" + price +
                ", volume:" + volume +
                ", marketCap:" + marketCap +
                ']';
    }
}
