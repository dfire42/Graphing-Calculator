class Vector : public List {

public:
	Vector(){}
	
	virtual Iterator<String> * createIterator() const 
	{
		return VectorIter<string>(this);
	}
	

	virtual int size() const 
	{
		return equationList.size();
	}

	virtual void add(string equation) 
	{
		equationList.push_back(equation);
	}

private:
	
	vector<string> equationList;

};
