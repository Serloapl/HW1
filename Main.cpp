#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<vector< double> > multiplication(vector<vector< double> > A, vector<vector< double> > B);
void visualization(vector<vector< double> > A);

vector<vector< double> > multiplication(vector<vector< double> > A, vector<vector< double> > B)
{	//function for matrix multiplication

	int N_rows_A = A.size();
	int N_cols_A = A[0].size();
	int N_rows_B = B.size();
	int N_cols_B = B[0].size();

	vector<vector< double> > C(N_rows_A, vector<double>(N_cols_B)); //Matrix Output

	if (N_cols_A != N_rows_B)
		cout << "Error: dimentions do not agree";
	else
	{
		for (int i = 0; i < N_rows_A; i++)
		{
			for (int j = 0; j < N_cols_B; j++)
			{
				C[i][j] = 0;
				for (int k = 0; k < N_cols_A; k++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return C;
	}
}

void visualization(vector<vector< double> > A)
{	// Function for matrix visualization

	int N_rows_A = A.size();
	int N_cols_A = A[0].size();

	cout << "A = (";

	for (int i = 0; i < N_rows_A; i++)
	{
		cout << A[i][0];
		for (int j = 1; j < N_cols_A; j++)
		{
			cout << ", " << A[i][j];
		}
		cout << ";" << endl << "     ";
	}
	//cout << ")";
}

int main()
{
	// ---------------------------------------------------------Data reading (beginning)
	string line;
	ifstream input("sample_00.in"); //input file
	vector<double> transition_aux;	//auxiliar vectors for reading
	vector<double> emission_aux;	//auxiliar vectors for reading
	vector<double> pi_aux;			//auxiliar vectors for reading
	double d;

	if (input.is_open())
	{
		//Getting Matrix A Transition
		getline(input, line);
		stringstream lineStream(line);

		while (lineStream >> d)
		{
			transition_aux.push_back(d);
			cout << d << endl;
		}

		//Getting Matrix B Emission
		getline(input, line);
		lineStream = stringstream(line);
		while (lineStream >> d)
		{
			emission_aux.push_back(d);
		}
		
		//Getting Matrix Pi (Initial)
		getline(input, line);
		lineStream = stringstream(line);
		while (lineStream >> d)
		{
			pi_aux.push_back(d);
		}

		input.close();
	}

	else
	{
		cout << "Unable to open file";
	}

	

	//Vector reordenation into matrices
	//Matrix A Transition
	int N_rows_A = int(transition_aux[0]);
	int N_cols_A = int(transition_aux[1]);
	int k = 2;

	vector<vector< double> > A(N_rows_A, vector<double>(N_cols_A));
	for (size_t i = 0; i < N_rows_A; i++)
	{
		for (size_t j = 0; j < N_cols_A; j++)
		{
			A[i][j] = transition_aux[k];
			k++;
		}
	}
	visualization(A);

	//Matrix B Emission
	int N_rows_B = int(emission_aux[0]);
	int N_cols_B = int(emission_aux[1]);
	k = 2;

	vector<vector<double>> B(N_rows_B, vector<double>(N_cols_B));
	for (size_t i = 0; i < N_rows_B; i++)
	{
		for (size_t j = 0; j < N_cols_B; j++)
		{
			B[i][j] = emission_aux[k];
			k++;
		}
	}
	visualization(B);

	//Matrix(vector) Pi (Initial)
	int N_cols_pi = int(pi_aux[1]);
	vector<vector<double > > pi(1, vector<double>(N_cols_pi));
	
	for (size_t i = 0; i < N_cols_pi; i++)
	{
		pi[0][i] = pi_aux[i+2];
	}
	visualization(pi);

	system("pause");

	//--------------------------------------------------------------Data reading (End)

	//------------------------------------------------------------- Multiplication (beginning)

	vector<vector<double> > output_aux; //Result matrix

	output_aux = multiplication(multiplication(pi, A), B);
	visualization(output_aux);
	system("pause");

	//----------------------------------------------------------------- Multiplication (end)

	//-----------------------------------------------------------------Output (beginning)

	int N_rows_o = output_aux.size();
	int N_cols_o = output_aux[0].size();

	vector<double> output; //Output vector (reshaped)

	output.push_back(double(N_rows_o));
	output.push_back(double(N_cols_o));

	for (size_t i = 0; i < N_rows_o; i++)
	{
		for (size_t j = 0; j < N_cols_o; j++)
		{
			output.push_back(output_aux[i][j]);
		}
	}

	ofstream myfile("sample_01.ans"); //Output to file
	if (myfile.is_open())
	{
		myfile << output[0];
		for (size_t i = 1; i < output.size(); i++)
		{
			myfile << " " << output[i];
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	//----------------------------------------------------------------------Output (end)

	return 0;
}









