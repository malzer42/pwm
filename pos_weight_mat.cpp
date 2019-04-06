/**
    pos_weight_mat.cpp: driver of the program
    Programmer: Pierre Abraham Mulamba
    @KAUST, Sat May 7, 2011, 01:05
    Last updated: Oct 10, 2011, 2:42.
    Bugs: The consensus sequence and the rate consensus sequence are not correct.
    To be done: 1.Fix the consensus_seq and the rate_cons_seq, 2. Implement the sliding windows,
    3.Compute the Information content for each position, 4. compute the pos_weight_mat based on the pos_freq_mat

    Usage: ./xpos_weight_matrix inputfilename1 inputfilename2 outputfilename
    example: ./xpos_weight_matrix nucleotide.seq nucleotide1.seq result
    where: nucleotide.seq is the input file 1 containing the sequences to be processed to create the pwm
    nucleotide1.seq is the input file 2 containing the sequence to be scanned
    result is the outputfilename

    Code for implementing the sliding windows
    vector< string > window[number_of_windows];
    while( getline( fin2 , line ) ){
    cout << endl<< line << endl;
    for(UI i = 0 ; i < number_of_windows ;i++ ){
    window[i].push_back(line.substr(i,fin1_sequence_length));
    cout << line.substr(i,fin1_sequence_length) << endl;
    }
    cout << "next line" << endl;
    }
*/

#include "pos_weight_mat.h"

int main(int argc , char *argv[])
{
   //section: Variables used to hold the version of the program , the name of the executable
  std::string version = "20190401";
  std::string prog = argv[0];								// prog = ./xpos_weight_mat ie it contains the . and / character
  std::string prog1(prog, 2, prog.size());					// prog1 = xpos_weight_mat ie the . and / characters are removed
  std::time_t currentTime; // variable for storing time
  std::time( &currentTime ); // store time in currentTime

  try{
    //section: checking the number of argument to provide at the command line
    if (argc != 4) {
      std::cout << "USAGE:\n" 
		<< " ./xpos_weight_mat input_file_name1 input_file_names2 output_file_name\n" 
		<< " ./xpos_weight_mat Executable program\n " 
		<< " input_file_name1 File containing sequences to generate the position weight matrix\n"
		<< " input_file_name2 File containing sequences to scan , create sliding windows and use the position weight matrix\n" 
		<< " output_file_name File to hold the results\n"
		<< " howto: From the command line type\n"
		<< " ./xpos_weight_mat bicoidMotif.seq Donor_acceptor.fa result\n\n";
      exit(0);
    }

    //section: system calls and display the purpose of the program
    system("clear");
    
    std::cout << std::asctime( std::localtime( &currentTime ) );
    
    Title theTitle(prog1 , version);

    Message aMessage("Program to Analyse DNA Sequences and Produce Statistics");
    //section; variables declaration and initialization
    //ifstream fin;  									// fin -- File in or input file
    std::ifstream fin1; 										// file input 1.
    std::ifstream fin2;										//file input 2
    
    fin1.open(argv[1] , std::ifstream::in);
    if ( !fin1 ) {
      std::cerr << std::endl << setw(140)<< "Input file could not be opened / was not provided as a 1st command line argument\n";
      exit(1);
    }

    fin2.open(argv[2] , std::ifstream::in);
    if ( !fin2 ) {
      std::cerr << std::endl << setw(140)<< "Input file could not be opened / was not provided as a 2nd command line argument\n";
      exit(1);
    }

    /*	section ; creating the nucleotides matrix
     * 	description: read a line from the input file 1. Each line read is saved as a row of the nucleotides matrix
     *      one character at a time.
     */

    std::string sequence;
    std::vector< std::string > nucleotides;
    while ( std::getline( fin1 , sequence ) ) {
      nucleotides.push_back(sequence); //the nucleotide matrix is created.
    }

    fin1.close();
    
    std::cout << std::setw(105) << "The Number of Sequences in the file " << argv[1] << " is :" << nucleotides.size() << '\n';
    std::cout << std::setw(107) << "The Length of each sequence in the file " << argv[1] << " is : " << (*nucleotides.begin()).size() <<"\n\n";
    
    //	section: converting all the characters of the  nucleotides matrix to lower case is created.
    for( std::vector<std::string >::iterator i = nucleotides.begin() ; i != nucleotides.end() ; i++){
      std::cout << *i << '\n';
      for( UI j = 0 ; j < (*i).size() ; j++){
	(*i).at(j) = tolower( (*i).at(j) );
	std::cout << (*i).at(j);
      }
      std::cout << '\n';
    }

    std::cout << '\n' << '\n' << "Conversion to lower done" << '\n';
    /*	section: computation -- counting the number of nucleotides a, c, g, and t at each position or column of the matrix nucleotides and creating
	the position frequency matrix (pos_freq_mat) of dimensions  BASE_NBR x COL: COL is the number of position and BASE_NBR is the number of base:4
	pos_freq_mat is a std::vector of std::vectors[The C++ Programming Language, Special ed. pp 836-837]
    */
    //string base("abcdefghijklmnopqrstuvwxyz");
    string base("acgt");					// equivalent to string base = "acgt" , holds the nucleotide a, c, g, and t
    
    std::vector< std::vector < int > > pos_freq_mat(base.size(),std::vector< int > ((*nucleotides.begin()).size()) );
    
    for(std::vector<string>::const_iterator i = nucleotides.begin() ; i != nucleotides.end() ; i++){
      for(UI col = 0 ; col < (*i).size() ; col++){
	for(UI k = 0 ; k < base.size(); k++){
	  if( (*i).at(col) == base.at(k)){
	    pos_freq_mat.at(k).at(col)++;
	  }
	  else{
	    ;
	  }
	}
      }
    }

    //for testing the creation of the position frequency matrix pos_freq_mat
    ofstream fout_pos_freq_mat;
    fout_pos_freq_mat.open("pos_freq_mat.dat" , ios::app);
    
    for (UI col = 0 ; col < (*nucleotides.begin()).size(); col++) {
      fout_pos_freq_mat << setw(2) << col+1;
      for (UI row = 0 ; row < base.size(); row++ ) {
	fout_pos_freq_mat << setw(8) << setprecision(2) << pos_freq_mat.at(row).at(col);
      }
      fout_pos_freq_mat << '\n';
    }
    
    for(std::vector<std::vector< int > >::const_iterator i = pos_freq_mat.begin() ; i != pos_freq_mat.end() ; i++){
      for(std::vector< int >::const_iterator j = (*i).begin() ; j != (*i).end() ; j++){
	std::cout << *j << '\t';
      }
      std::cout << '\n';
    }
    
    fout_pos_freq_mat.close();
    
    // comment the above section at successfull creation of the position frequency matrix - pos_freq_mat
    
    /*	section: computing total number of observations -- the sum of all nucleotides occurences in a column or position
	this sum is used in the transformation of the position frequency matrix to position weight matrix
    */
    std::cout << '\n';
    std::vector<int> position[ (*nucleotides.begin()).size() ];	//(*nucleotides.begin()).size() gives the number of column in the matrix nucleotides
    std::vector<int> total_pos( (*nucleotides.begin()).size());
    
    for (UI j = 0 ; j < (*nucleotides.begin()).size() ; j++) {
      for (UI i = 0; i < base.size() ; i++) {
	position[j].push_back( pos_freq_mat[i][j] );
      }
      std::cout << *max_element( position[j].begin() , position[j].end() ) << '\t' ;
      total_pos[j] = sumVec(position[j]);
    }
    std::cout << '\n' <<'\n';

    //	section: create a site_specific_scoring_matrix based on the pos_freq_mat and total_pos
    std::vector< std::vector < double> > site_spec_scoring_mat(base.size() , std::vector<double> ((*nucleotides.begin()).size()));
    for (UI row = 0; row < base.size();row++) {
      for (UI col = 0 ; col <= (*nucleotides.begin()).size() - 1 ; col++ ) {
	site_spec_scoring_mat.at(row).at(col) = double ( pos_freq_mat.at(row).at(col)) / (total_pos.at(col));
      }
    }

    //for testing the creation of the site_specific_scoring_matrix
    ofstream fout_site_spect;
    fout_site_spect.open("site_spec_scoring_mat.dat" , ios::app);
    for (UI col = 0 ; col < (*nucleotides.begin()).size(); col++) {
      fout_site_spect << setw(2) << col+1;
      for (UI row = 0 ; row < base.size(); row++ ) {
	fout_site_spect << setw(8) << setprecision(3) << site_spec_scoring_mat.at(row).at(col);
      }
      fout_site_spect << '\n';
    }

    fout_site_spect.close();
    // comment the above section at successfull creation of the site_specific_scoring_matrix
    //	section: creating a log-odd site specific scoring matrix based on the site_specific_scoring_matrix
    std::vector< std::vector < double > > log_odd_site_spec_scoring_mat(base.size() , std::vector<double> ((*nucleotides.begin()).size()));
    for (UI row = 0; row < base.size();row++) {
      for (UI col = 0 ; col <= (*nucleotides.begin()).size() - 1 ; col++ ) {
	if (site_spec_scoring_mat.at(row).at(col) != 0.0 )
	  //value = site_spec_scoring_mat.at(col)*4;
	  log_odd_site_spec_scoring_mat.at(row).at(col) = log2((site_spec_scoring_mat.at(row).at(col))/FACTOR);
	//log_odd_site_spec_scoring_mat.at(row).at(col) = log2( (site_spec_scoring_mat.at(row).at(col)/0.25) +1.0 );
	else
	  log_odd_site_spec_scoring_mat.at(row).at(col) = 0.0;
      }
    }

    //for testing the creation of the log_odd_site_spec_scoring_mat
    ofstream fout_log_odd_site_spec;
    fout_log_odd_site_spec.open("log_odd_site_spec.dat" , ios::app);
    
    for (UI col = 0 ; col < (*nucleotides.begin()).size(); col++) {
      fout_log_odd_site_spec << setw(2) << col+1;
      for (UI row = 0 ; row < base.size(); row++ ) {
	fout_log_odd_site_spec << setw(8) << setprecision(2) << log_odd_site_spec_scoring_mat.at(row).at(col);
      }
      fout_log_odd_site_spec << '\n';
    }

    fout_log_odd_site_spec.close();
    // comment the above section at successfull creation of the log_odd_site_specific_scoring_matrix
    
    /*	section: find the maximum value at each std::vector colum (position) of the matrix pfm then locate the nucleotide
	that has the high frequency in that column then create the consensus sequence and the common consensus sequence
	After finding the consensus sequence (cs) and the common consensus sequence (ccs) we compute the score of  cs and ccs
	we also compute the low (beginning of the ccs) and high value (end of the css) of the ccs
    */
    std::vector< double > max_pos((*nucleotides.begin()).size());
    std::vector< double > position_log[(*nucleotides.begin()).size()];
    
    for(UI j = 0 ; j < (*nucleotides.begin()).size() ; j++){
      for(UI i = 0 ; i < base.size() ; i++){
	position_log[j].push_back( log_odd_site_spec_scoring_mat[i][j] );
      }
    }
    std::string cnsnss_sq;
    std::string consensus_seq;
    std::string rate_cons_seq;

    for (UI j = 0 ; j < (*nucleotides.begin()).size(); j++){
      for(UI i = 0 ; i < base.size() ; i++){
	if(*max_element( position_log[j].begin() , position_log[j].end()) != 0)
	  cnsnss_sq[j] = base[i];
      }
    }

    std::cout << '\n' << "The consensus sequence : ";
    for(UI i = 0 ; i < cnsnss_sq.size() ; i++){
      std::cout << cnsnss_sq[i];
    }

    std::cout << "done " << '\n';
    
    for (UI j = 0 ; j < (*nucleotides.begin()).size() ; j++) {
      for (UI i = 0 ; i < base.size() ; i++) {
	if ( max_pos[j] < log_odd_site_spec_scoring_mat[i][j] ) {
	  max_pos[j] = log_odd_site_spec_scoring_mat[i][j];
	  consensus_seq[j] = base[i];
	  /*if else Bloc to compute the rate consensus sequence. Comment it to display the consensus sequence
	    if( max_pos[j] >= int( nucleotides.size()/2 ) ){
	    rate_cons_seq[j] = consensus_seq[j];
	    }
	    else{
	    consensus_seq[j] = consensus_seq[j];
	    rate_cons_seq[j] = ' ';
	    } end of the bloc if else to displace the rate consensus sequence
	  */
	}
	else {
	  max_pos[j] = max_pos[j];
	}
      }
    }

    //	section: Creating a matrix containing all sequences of the input file 2
    std::vector< string > windows;
    while ( getline(fin2, sequence) ) {
      windows.push_back(sequence);
    }
    
    //	section: converting all nucleotide in the windows matrix to lower case
    for(std::vector<string>::iterator i = windows.begin() ; i != windows.end() ; i++){
      for(UI j = 0 ; j < (*i).size() ; j++){
	(*i).at(j) = tolower( (*i).at(j));
      }
    }

    std::cout << setw(105) << "The Number of Sequences in the file " << argv[2] << " is :" << windows.size() << '\n';
    std::cout << setw(107) << "The Length of each sequence in the file " << argv[2] << " is : " << (*windows.begin()).size() << '\n'<< '\n';
    std::cout << setw(111) << "The Number of sliding windows per line in file " << argv[2] << " is : " << (*windows.begin()).size() - (*nucleotides.begin()).size() +1
	 << '\n' << '\n';
    std::cout << setw(170)
	      << "The score value gives up an indication that the sequence has properties similar to those of the sequences used to derive the matrix"
	      << '\n' << '\n';
    
    //	section: save the result in an output file
    //Message("Secton to Display The Position Frequency Matrix");
    char *outfile = new char[strlen(argv[3])+1];
    strcpy(outfile , argv[3]);
    //[3];
    //const char *ext =".txt";
    //strcat(outfile,ext);
    ofstream fout;
    fout.exceptions( ofstream::failbit | ofstream::badbit);
    fout.open(outfile , ios::app);
    fout << '#' <<asctime( localtime( &currentTime ) );// << '\n' << '#' << '\n';
    fout << '#' << setw(105) << "The Number of Sequences in the file " << argv[1] << " is :" << nucleotides.size() << '\n';
    fout << '#' << setw(107) << "The Length of each sequence in the file " << argv[1] << " is : " << (*nucleotides.begin()).size() << '\n' << '#' << '\n';
    fout << '#' << setw(105) << "The Number of Sequences in the file " << argv[2] << " is :" << windows.size() << '\n';
    fout << '#' << setw(107) << "The Length of each sequence in the file " << argv[2] << " is : " << (*windows.begin()).size() << '\n' <<'#'<< '\n';
    fout << '#' << setw(111) << "The Number of sliding windows per line in file " << argv[2] << " is : "
	 << (*windows.begin()).size() - (*nucleotides.begin()).size() +1
	 << '\n' <<'#' << '\n';
    fout << '#' << setw(170)
	 << "The score value gives up an indication that the sequence has properties similar to those of the sequences used to derive the matrix"
	 << '\n' << '#' << '\n';
    //fout << '#' << "The Consensus Sequence is :";

    //for(UI col = 0 ; col <= sequence_length - 1 ; col++) fout << consensus_seq[col];
    
    fout << '#' << '\n';

    std::string underline(110 , '-');
    
    //print_std::vector(max_pos , 3);
    
    fout << '#' << setw(112) << underline << '\n'
	 << '#' << setw(5) << "Pos" << setw(7) << "A" << setw(7) <<"C" << setw(7) << "G" << setw(7) << "T"
	 << setw(7) << "%A" << setw(7) << "%C" << setw(8) <<"%G" << setw(8) << "%T" << setw(10) << "TotPos"
	 << setw(9) << "MaxPos" << setw(15) << "ConsensusSeq" << setw(15) << "Rate_Cons_seq" <<  '\n'
	 << '#' << setw(112) << underline << '\n';

    for (UI col = 0 ; col <= (*nucleotides.begin()).size() -1 ; col++) {
      fout << setw(5) << col+1;							// col+1 so that the count starts from 1 but not 0
      for (UI row = 0 ; row < base.size() ; row++) {
	fout << setw(7) << setprecision(2) << log_odd_site_spec_scoring_mat[row][col];
      }

      for (UI row = 0 ; row < base.size() ; row++) {
	fout << setw(8) << setprecision(4) << (pos_freq_mat[row][col] * 100.0)/(nucleotides.size());
      }
      fout << setw(7) << total_pos[col] << setw(9) << *max_element( position_log[col].begin() , position_log[col].end() ) << setw(13) << consensus_seq[col]
	//fout << setw(7) << total_pos[col] << setw(9) << max_pos[col] << setw(13) << consensus_seq[col]
	   << setw(15) << rate_cons_seq[col] << '\n';
      //std::cout << consensus_seq[col];
    }

    fout << '#' << setw(112) << underline << '\n'
	 << '#' << setw(5) << "Pos" << setw(7) << "A" << setw(7) <<"C" << setw(7) << "G" << setw(7) << "T"
	 << setw(7) << "%A" << setw(7) << "%C" << setw(8) <<"%G" << setw(8) << "%T" << setw(10) << "TotPos"
	 << setw(9) << "MaxPos" << setw(15) << "ConsensusSeq" << setw(15) << "Rate_Cons_seq" << '\n'
	 << '#' << setw(112) << underline << '\n' << '\n';

    //section: creating sliding windows and saving the result in the output file
    ofstream score_out("score.dat");			//output file to hold the score  the values used to compute the score
    UI number_of_windows = ( (*windows.begin()).size() - (*nucleotides.begin()).size() ) +1;
    for (UI row = 0 ; row < windows.size(); row++) {
      std::cout << '\n' << windows[row] << '\n';
      fout << '\n' << windows[row] << '\n';
      score_out << row+1 << '\t' ;
      for ( UI i = 0 ; i < number_of_windows ; i++ ) {
	double score = 0.0;
	string slide = windows[row].substr( i , (*nucleotides.begin()).size());
	std::cout << slide << " : " ;
	fout << slide << " : " ;
	for (UI pos = 0 ; pos < slide.size(); pos++) {
	  for (UI iter = 0 ; iter < base.size() ; iter++) {
	    if ( slide[pos] == base[iter] ) {
	      std::cout << setprecision(3) << log_odd_site_spec_scoring_mat[iter][pos] << '\t';
	      fout << setprecision(3) << log_odd_site_spec_scoring_mat[iter][pos] << '\t';
	      score_out << setprecision(3) << log_odd_site_spec_scoring_mat[iter][pos] << '\t';
	      score += log_odd_site_spec_scoring_mat[iter][pos];
	    }
	  }

	}
	if (score >= THRESHOLD) {
	  std::cout << "score :"  << setprecision(3) << score << "\t(+)" << '\n';
	  fout << setprecision(3) << score << "\t(+)" << '\n';
	  score_out << setprecision(3) <<  score << "\t(+)"<< '\n';
	}
	else {
	  std::cout << "score :"  << setprecision(3) << score << "\t(-)" << '\n';
	  fout << setprecision(3) << score << "\t(-)" << '\n';
	  score_out << setprecision(3) <<  score << "\t(-)" << '\n';
	}
	slide.clear();
      }
    }

    fout.close();

    delete[] outfile;
    
    std::cout << '\n';
    std::cout << setw(120) << "The results is saved is the output file : "<< '\n' << '\n'
	 << setw(100) <<  outfile << '\n' << '\n';
  }
  catch ( ofstream::failure e) {
    cerr << setw(140) << "Output file could not be opened/was not provided as a second command line argument" << '\n' << '\n';
  }
  catch ( ... ) {
    cerr << "Unknow expection thrown " << '\n';
  }
  
  End th_End(prog1);
}
