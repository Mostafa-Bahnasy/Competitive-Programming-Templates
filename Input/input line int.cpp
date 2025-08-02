void ReadIntLine(vector<int>& numbers)
{
    string line;
    getline(cin, line);

    istringstream is(line);

    numbers = vector<int>(istream_iterator<int>(is), istream_iterator<int>());
}