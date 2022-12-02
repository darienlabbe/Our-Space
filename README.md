# Our-Space: Overview
This social media project was a class project where I needed to create a program that could parse a ".json" file and create user html files. Storing their location, profile image, who they follow, who follows them, and who their mutuals are. All of this information is then put together and linked so that from the home page you can visit all the users in the social media and also click on the user pages from that user's follow list, followers list, and mutuals list.

# Our-Space: Project Structure
The project uses two classes, one to handle individual users, creating user html pages, and parsing the "input.json" file and another class to handle creating an index.html page that holds all user links and the logo. There are two options for input files, one is for four users to demonstrate the functionality of the project and one is for 1,000 users. Whichever one that you wish to use should be copied over into the file "input.json" so that the program can use the correct data. There is also an included Makefile that will run the program.

# Our-Space: Time
When using the input of 4 users in the json file, the program compiles very quickly. When compiling with the 1,000 users, the time to create all 1,000 user htmls can take a bit and how fast will vary depending on your computer. For me it took anywhere from 1-4 minutes to compile and run through the program.
