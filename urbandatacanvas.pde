Table table;
int counter;



void setup() {
  size(1920, 1080);
  table = loadTable("urban_data.csv", "header");
  println(table.getRowCount() + " total rows in table");
  
  for (TableRow row : table.rows()) {
    
    String time = row.getString("Timestamp");
    String station = row.getString("Station");
    String object = row.getString("Object");
    int count = row.getInt("Count");
    
    
    int[] dateTime = int(splitTokens(timeStamp, "- :"));
    
    int year = dateTime[0];
    int month = dateTime[1];
    int day = dateTime[2];
    
    int hour = dateTime[3];
    int minute = dateTime[4];
    int second = dateTime[5];
    
  }
  
}
