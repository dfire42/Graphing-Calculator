class Iterator {

public:

	virtual void First();
	virtual void Next();
	virtual bool isDone() const;
	virtual string currentIndex() const = 0;

};
