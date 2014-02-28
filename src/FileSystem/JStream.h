#ifndef JSTREAM_H_
#define JSTREAM_H_

class JStream
{
public:
	JStream();
	~JStream();

	bool Open();
	void Close();

	bool Read();
	bool Write();
};

#endif