# MapD IoT test

### Contents:
- deviceCode: Contains the code for the IoT device. You can use it with Arduino IDE after installing the required libraries.
- myServer: Contains the server code. Server adds coming data to log.csv. Just run `$ npm install` then `$ npm start`.
- 3DcaseAndCover: Contains case and cover designs for 3D printing.

### Connection to MapD server:
- First you need to create a table with matching criteria to log.csv: timeStamp, string, int, int.
- Second stream the csv to that table `$ tail -F file/to/be/streamed/log.csv | Mapd/installation/directory/bin/StreamImporter <Table name>  <Database> -u <Username> -p <Password> --delim ',' --batch 10 --retry_count 360 --retry_wait 10 --null null --port <Port>`
