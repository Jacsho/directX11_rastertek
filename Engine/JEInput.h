#ifndef _JEINPUT_H_
#define _JEINPUT_H_

//==============================================
// Class name: JEInput
//==============================================
class JEInput
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		bool m_keys[256];

	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JEInput();

		JEInput(
			const JEInput &
		);

		~JEInput();

	//==============================================
	//				   METHODS
	//==============================================
	public:
		void Initialize();

		void KeyDown(
			unsigned int
		);

		void KeyUp(
			unsigned int
		);

		bool IsKeyDown(
			unsigned int
		);
};

#endif
