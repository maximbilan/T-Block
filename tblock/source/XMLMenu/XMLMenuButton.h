#ifndef _XMLMenuBUTTON_H_
#define _XMLMenuBUTTON_H_

class XMLMenuButton
{
	protected:
		bool m_backButton;

	public:
		XMLMenuButton();
		virtual ~XMLMenuButton();

		bool isBackButton() const;
};

inline bool XMLMenuButton::isBackButton() const
{
	return m_backButton;
}

#endif