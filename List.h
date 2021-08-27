class List { 

public: 
	
	virtual Iterator<String> * CreateIterator() const = 0;
	virtual int size() const = 0;
	virtual void add(string equation);

};
