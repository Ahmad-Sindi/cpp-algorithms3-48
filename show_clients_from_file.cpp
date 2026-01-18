#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

/*
 * Algorithm Challenge – Level 3 | #48 Show All Clients From File
 *
 * This program demonstrates how to read client records from one or more text files, convert each line into a structured record, and display the data in a formatted table.
 *
 * Engineering Flow:
 *   - Open text files automatically
 *   - Read each line (each line represents one client)
 *   - Parse the line using a custom delimiter (#//#)
 *   - Store data inside a structured record (struct)
 *   - Display all clients in a formatted table
 */

// File names (each file may contain client records)
const string ClientFileName1 = "Clients.txt";
const string ClientFileName2 = "AddNewClient.txt";

// Structure that represents a client record
struct ClientStructData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phon;
    double AccountBalance;
};

// Splits a string based on a given delimiter
vector<string> SplitString(string S1, string Delim)
{
    vector<string> VecString;
    short Position = 0;
    string Token;

    while ((Position = S1.find(Delim)) != string::npos)
    {
        Token = S1.substr(0, Position);

        if (Token != "")
        {
            VecString.push_back(Token);
        }

        S1.erase(0, Position + Delim.length());
    }

    if (S1 != "")
    {
        VecString.push_back(S1);
    }

    return VecString;
}

// Converts a single line of text into a client structure
ClientStructData ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    ClientStructData Client;
    vector<string> ClientData = SplitString(Line, Seperator);

    Client.AccountNumber   = ClientData[0];
    Client.PinCode         = ClientData[1];
    Client.Name            = ClientData[2];
    Client.Phon            = ClientData[3];
    Client.AccountBalance  = stod(ClientData[4]);

    return Client;
}

// Loads all client records from a file into a vector
vector<ClientStructData> LoadClientsDataFromFile(string FileName)
{
    vector<ClientStructData> VecClients;
    fstream FileClients;

    FileClients.open(FileName, ios::in); // Open file in read mode

    if (FileClients.is_open())
    {
        string Line;
        ClientStructData Client;

        // Each line represents one client
        while (getline(FileClients, Line))
        {
            Client = ConvertLineToRecord(Line);
            VecClients.push_back(Client);
        }

        FileClients.close();
    }

    return VecClients;
}

// Prints a single client record in table format
void PrintClientRecord(ClientStructData Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(15) << left << Client.PinCode;
    cout << "| " << setw(15) << left << Client.Name;
    cout << "| " << setw(10) << left << Client.Phon;
    cout << "| " << setw(10) << left << Client.AccountBalance;
}

// Prints all clients in a formatted table
void PrintAllClientsData(vector<ClientStructData> vClients)
{
    cout << "\n\t\t\tClient List (" << vClients.size() << ") Client(s)\n";
    cout << "--------------------------------------------------------------------------\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(15) << "Pin Code";
    cout << "| " << left << setw(15) << "Client Name";
    cout << "| " << left << setw(10) << "Phone";
    cout << "| " << left << setw(10) << "Balance\n";

    cout << "--------------------------------------------------------------------------\n";

    for (ClientStructData Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout << "--------------------------------------------------------------------------\n";
}

int main()
{
    // Load and display clients from first file
    vector<ClientStructData> ClientsFromFile1 = LoadClientsDataFromFile(ClientFileName1);
    PrintAllClientsData(ClientsFromFile1);

    // Load and display clients from second file
    vector<ClientStructData> ClientsFromFile2 = LoadClientsDataFromFile(ClientFileName2);
    PrintAllClientsData(ClientsFromFile2);

    return 0;
}
