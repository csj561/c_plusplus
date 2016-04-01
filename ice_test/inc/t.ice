
module Pri
{
	sequence<int> seqOpt;
	dictionary<byte,seqOpt> dict;
	exception Err{seqOpt maxi;};
	interface xyd
	{
		//seqOpt fun();

		int pri(out int i) 
			throws  Err;
	};
	interface Xu
	{
		void add(xyd * x);
		xyd* get();
	};
};
