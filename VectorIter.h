class VectorIter : public Iterator {

public:

	VectorIter(const VectorIter<string> * l)
	{
		list = l;
		vector_index = 0;
	}
	
	virtual void First() 
	{
		vector_index = 0;
	}
	
	virtual void Next()
	{
		vector_index++;
	}

	virtual bool isDone() const 
	{
		if(list->size == vector_index)
		{
			return true;
		}
			
		return false;
	}

	virtual string currentIndex
	{
		if(isDone())
		{
			return;
		}

		return list[vector_index];
	}		
		
private: 
	vectorIter<string> * list;
	int vector_index;

};
