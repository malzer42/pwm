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

/********************************************************************************
                                   
                                    Copyright (c) 2019 DTI, inc.
                                    All rights reserved

 ********************************************************************************/
#include "pos_weight_mat.h"

void check_file_opened(std::ifstream& fin){
  if(!fin){
    std::cerr << "Input file could not be opened /was not provided as a command line argument\n";
    exit(1);
  }
}


int main(int argc , char *argv[])
{
  //section: Variables used to hold the version of the program , the name of the executable

  std::string prog = argv[0];								// prog = ./xpos_weight_mat ie it contains the . and / character
  std::string prog1(prog, 1, prog.size());					// prog1 = xpos_weight_mat ie the . and / characters are removed
  std::time( &currentTime ); // store time in currentTime

  try{
    argument(argc);
    //section: system calls and display the purpose of the program
    system("clear");
    
    std::cout << std::asctime( std::localtime( &currentTime ) );
    
    Title theTitle(prog1 , version);

    Message aMessage("Program to Analyse DNA Sequences and Produce Statistics");
        
    std::ifstream fin1;
    fin1.open(argv[1] , std::ifstream::in);
    check_file_opened(fin1);
    
    std::vector< std::string > nucleotides = create_nucleotides_matrix(fin1);
    
    fin1.close();

    unsigned int nSeqInputFile = 0;
    nSeqInputFile = (nucleotides.size());
    
    unsigned int lengthSeqInputFile = 0;
    lengthSeqInputFile = (*nucleotides.begin()).length() ;
    
    
    
    std::cout << std::setw(105) << "The Number of Sequences in the file " << argv[1] << " is :" << nSeqInputFile << '\n';
    std::cout << std::setw(107) << "The Length of each sequence in the file " << argv[1] << " is : " << lengthSeqInputFile  <<"\n\n";
    
    /*	section: computation -- counting the number of nucleotides a, c, g, and t at each position or column of the matrix nucleotides and creating
	the position frequency matrix (pos_freq_mat) of dimensions  BASE_NBR x COL: COL is the number of position and BASE_NBR is the number of base:4
	pos_freq_mat is a std::vector of std::vectors[The C++ Programming Language, Special ed. pp 836-837]
    */
    std::vector<std::vector<int>> pos_freq_mat = create_pwm(nucleotides);
    print(pos_freq_mat);

    nucleotides.clear();
        
    /*	section: computing total number of observations -- the sum of all nucleotides occurences in a column or position
	this sum is used in the transformation of the position frequency matrix to position weight matrix
    */

    std::vector<int> total_pos = compute_total_position(pos_freq_mat, lengthSeqInputFile);
    
    // Section: create a site_specific_scoring_matrix based on the pos_freq_mat and total_pos
    
    std::vector< std::vector < double> > site_spec_scoring_mat(base.size() , std::vector<double> (lengthSeqInputFile));
    for (unsigned int  row = 0; row < base.size();row++) {
      for (unsigned int  col = 0 ; col <= lengthSeqInputFile  - 1 ; col++ ) {
	site_spec_scoring_mat[row][col] = double ( pos_freq_mat[row][col]) / (total_pos[col]);
      }
    }
    
    // Section: creating a log-odd site specific scoring matrix based on the site_specific_scoring_matrix
    
    std::vector< std::vector < double > > log_odd_site_spec_scoring_mat(base.size() , std::vector<double> (lengthSeqInputFile));
    for (unsigned int row = 0; row < base.size();row++) {
      for (unsigned int col = 0 ; col <= lengthSeqInputFile - 1 ; col++ ) {
	if (site_spec_scoring_mat.at(row).at(col) != 0.0 )
	  log_odd_site_spec_scoring_mat.at(row).at(col) = log2((site_spec_scoring_mat.at(row).at(col))/FACTOR);
	else
	  log_odd_site_spec_scoring_mat.at(row).at(col) = 0.0;
      }
    }

    
    
    
    
    /*	section: find the maximum value at each std::vector colum (position) of the matrix pfm then locate the nucleotide
	that has the high frequency in that column then create the consensus sequence and the common consensus sequence
	After finding the consensus sequence (cs) and the common consensus sequence (ccs) we compute the score of  cs and ccs
	we also compute the low (beginning of the ccs) and high value (end of the css) of the ccs
    */
    std::vector< double > max_pos;
    max_pos.resize(lengthSeqInputFile);
    
    std::vector< double > position_log[lengthSeqInputFile];
    
    for(unsigned int j = 0 ; j < lengthSeqInputFile ; j++){
      for(unsigned int i = 0 ; i < base.size() ; i++){
	position_log[j].push_back( log_odd_site_spec_scoring_mat[i][j] );
      }
    }
    
    //std::string consensus_seq = "";
    // std::string rate_cons_seq="";

    /* for (unsigned int j = 0 ; j < lengthSeqInputFile; j++){
      for(unsigned int i = 0 ; i < base.size() ; i++){
	if( *max_element( position_log[j].begin() , position_log[j].end()) != 0)
	  consensus_seq[j] = base[i];
      }
    }
    */
    
    //std::cout << "\nThe consensus sequence : " << consensus_seq;
    // std::cout << "Did we reach this level at all\n";
    // consensus_seq.clear();
    /*
    for (unsigned int j = 0 ; j < lengthSeqInputFile ; j++) {
      for (unsigned int i = 0 ; i < base.size() ; i++) {
	if ( max_pos[j] < log_odd_site_spec_scoring_mat[i][j] ) {
	  max_pos[j] = log_odd_site_spec_scoring_mat[i][j];
	  consensus_seq[j] = base[i];
	  if( max_pos[j] >= int( nSeqInputFile/2 ) ){
	    rate_cons_seq[j] = consensus_seq[j];
	  }
	  else{
	    consensus_seq[j] = consensus_seq[j];
	    rate_cons_seq[j] = ' ';
	  }
	}
	else {
	  max_pos[j] = max_pos[j];
	}
      }
    }
    */
    //	section: Creating a matrix containing all sequences of the input file 2
    
    std::ifstream fin2;										//file input 2
    fin2.open(argv[2] , std::ifstream::in);
    check_file_opened(fin2);
    std::vector< std::string > windows = create_nucleotides_matrix(fin2);

    std::cout << setw(105) << "The Number of Sequences in the file " << argv[2] << " is :" << windows.size() << '\n';
    std::cout << setw(107) << "The Length of each sequence in the file " << argv[2] << " is : " << (*windows.begin()).size() << '\n'<< '\n';
    std::cout << setw(111) << "The Number of sliding windows per line in file "
	      << argv[2] << " is : " << (*windows.begin()).size() - lengthSeqInputFile +1
	      << '\n' << '\n';

    std::cout << setw(170)
	      << "The score value gives up an indication that the sequence has properties similar to those of the sequences used to derive the matrix\n\n";
        
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
    fout << '#' << setw(105) << "The Number of Sequences in the file " << argv[1] << " is :" << nSeqInputFile << '\n';
    fout << '#' << setw(107) << "The Length of each sequence in the file " << argv[1] << " is : " << lengthSeqInputFile << '\n' << '#' << '\n';
    fout << '#' << setw(105) << "The Number of Sequences in the file " << argv[2] << " is :" << windows.size() << '\n';
    fout << '#' << setw(107) << "The Length of each sequence in the file " << argv[2] << " is : " << (*windows.begin()).size() << '\n' <<'#'<< '\n';
    fout << '#' << setw(111) << "The Number of sliding windows per line in file " << argv[2] << " is : "
	 << (*windows.begin()).size() - lengthSeqInputFile +1
	 << '\n' <<'#' << '\n';
    fout << '#' << setw(170)
	 << "The score value gives up an indication that the sequence has properties similar to those of the sequences used to derive the matrix"
	 << '\n' << '#' << '\n';
    //fout << '#' << "The Consensus Sequence is :";

    //for(unsigned int col = 0 ; col <= sequence_length - 1 ; col++) fout << consensus_seq[col];
    
    fout << '#' << '\n';

    std::string underline(110 , '-');
    
    //print_std::vector(max_pos , 3);
    
    fout << '#' << setw(112) << underline << '\n'
	 << '#' << setw(5) << "Pos" << setw(7) << "A" << setw(7) <<"C" << setw(7) << "G" << setw(7) << "T"
	 << setw(7) << "%A" << setw(7) << "%C" << setw(8) <<"%G" << setw(8) << "%T" << setw(10) << "TotPos"
	 << setw(9) << "MaxPos" << setw(15) << "ConsensusSeq" << setw(15) << "Rate_Cons_seq" <<  '\n'
	 << '#' << setw(112) << underline << '\n';

    for (unsigned int col = 0 ; col <= lengthSeqInputFile -1 ; col++) {
      fout << setw(5) << col+1;							// col+1 so that the count starts from 1 but not 0
      for (unsigned int row = 0 ; row < base.size() ; row++) {
	fout << setw(7) << setprecision(2) << log_odd_site_spec_scoring_mat[row][col];
      }

      for (unsigned int row = 0 ; row < base.size() ; row++) {
	fout << setw(8) << setprecision(4) << (pos_freq_mat[row][col] * 100.0)/(nSeqInputFile);
      }
      fout << setw(7) << total_pos[col] << setw(9) << *max_element( position_log[col].begin() , position_log[col].end() )
	//fout << setw(7) << total_pos[col] << setw(9) << max_pos[col] << setw(13) << consensus_seq[col]
	   << setw(15)  << '\n';
      //std::cout << consensus_seq[col];
    }

    fout << '#' << setw(112) << underline << '\n'
	 << '#' << setw(5) << "Pos" << setw(7) << "A" << setw(7) <<"C" << setw(7) << "G" << setw(7) << "T"
	 << setw(7) << "%A" << setw(7) << "%C" << setw(8) <<"%G" << setw(8) << "%T" << setw(10) << "TotPos"
	 << setw(9) << "MaxPos" << setw(15) << "ConsensusSeq" << setw(15) << "Rate_Cons_seq" << '\n'
	 << '#' << setw(112) << underline << '\n' << '\n';

    //section: creating sliding windows and saving the result in the output file
    ofstream score_out("score.dat");			//output file to hold the score  the values used to compute the score
    unsigned int number_of_windows = ( (*windows.begin()).size() - lengthSeqInputFile ) +1;
    for (unsigned int row = 0 ; row < windows.size(); row++) {
      std::cout << '\n' << windows[row] << '\n';
      fout << '\n' << windows[row] << '\n';
      score_out << row+1 << '\t' ;
      for ( unsigned int i = 0 ; i < number_of_windows ; i++ ) {
	double score = 0.0;
	string slide = windows[row].substr( i , lengthSeqInputFile);
	std::cout << slide << " : " ;
	fout << slide << " : " ;
	for (unsigned int pos = 0 ; pos < slide.size(); pos++) {
	  for (unsigned int iter = 0 ; iter < base.size() ; iter++) {
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
