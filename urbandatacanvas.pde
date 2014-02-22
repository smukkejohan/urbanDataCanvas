Table table;
int counter;



void setup() {
  size(1920/2, 1080/2);
  
  println("Loading data...");
  table = loadTable("urban_data_v2.csv", "header");
  println(table.getRowCount() + " total rows in table");
  
  for (TableRow row : table.rows()) {
    
    String time = row.getString("Timestamp");
    String station = row.getString("Station");
    String object = row.getString("Object");
    int count = row.getInt("Count");
    
    int[] dateTime = int(splitTokens(time, "- :"));
    
    int year = dateTime[0];
    int month = dateTime[1];
    int day = dateTime[2];
    
    int hour = dateTime[3];
    int minute = dateTime[4];
    int second = dateTime[5];  
  }
  
}


void draw() {
  background(0);
}


