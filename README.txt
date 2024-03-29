Dynamic File Viewer
Version 1

DESIGN -- FINAL

Global Variables:

	const int windowHeight = 10;
	vector<string> link_number_files;
	int link_number = 0;

Functions:

	
	►bool check_for_anchor(const string & line)
		
		Checks file lines for anchors.

	►string get_anchor_file(string & anchor)

		When an anchor is found within a line of a file, this function 
		extracts the file name component of the anchor and returns it.
	
	►string get_anchor_text(string & anchor)

		When an anchor is found within a line of a file, this function
		extracts the text component of the anchor and returns it.

	►string format_anchor(string & anchor)

		When an anchor is found within a line of a file, this function
		formats the anchor in the file into the specified display format.

		Implementation Notes: Uses the get_anchor_text function to create 
					a new string to replace the anchor in the file.

	►void display(const string & file_name, const vector<string> & v_document_lines, int ix_current_line)

		Creates the file viewer interface.

		Implementation Notes: Uses global variable windowHeight to determine the number
					of lines that will appear on any page.

	►void open_file(string & file_name, vector<string> & v_document_lines, int ix_current_line)
	
		Handles the opening of files specified by the user.

		Implementation Notes: Uses the above anchor-handling functions to produce an
					edited copy of the file to be opened that displays the
					file according to the project specifications.

	►void run_file_viewer()
		
		Runs the file viewer.  Takes input from the user to implement specific commands.

		Implementation Notes: Utilizes only the display and open_file functions in combination
					with switch statements to handle user commands.

		

	