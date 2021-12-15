**

## Metar Project


**Goals**

 - Design a simple program that retrieves and displays METAR data and also allows a user to create/edit a flight log.

**Boundaries/Scope**

 - Design fully functioning METAR report and logbook from scratch 

**Success Criteria**

 - Program functions properly without any bugs/errors
 
**Constraints**

 - Program must be completed by the end of Fall 2021 semester

**Assumptions**

 - My computer is capable of running necessary software to complete this project
 - I will have to learn how to properly use Qt Creator

**Stakeholders**

 - Professor Vanselow - Evaluates my project and determines my grade
 - Potential Employers - This project will be added to my student portfolio and will give me an opportunity to showcase my work and abilities

**Instruction**

Upon opening the program, the user will have the option of using the METAR function or the logbook function. Let's begin the METAR report. In the input box beside "Enter Airport ID", the user will type in a proper ICAO identifier and then click the "Search" button.

The program will retrieve the correspinding METAR information and display the raw report in textbox labeled "Raw METAR". Specific sections of the report that are relevant to prefilght checklists will be displayed in labeled textboxes on the left-hand side of the program interface.

To utilize the logbook, simply click on the "Logbook" button. A new window will appear which will allow the user to enter flight data into corresponding fields. Once the information has been entered into each field, the user can click "Add Entry" to add the data to the table below. Also, the user has the option to load a previously created logbook XML file by clicking "Load File". If a user wishes to delete an entry, they can simply click on the row in the table and then click "Delete Entry". Once all data has been entered, the user can click "Save File" to save the data into an XML file.  
