#ifndef UTILITIES_CLI_MENU_H
#define UTILITIES_CLI_MENU_H

#include "utilities-callback.h"
#include <vector>

namespace Utilities
{
  class CLIMenu
  {
  public:
    CLIMenu(const std::string& title);

    void addChoice(const std::string& choicename,
                   const Utilities::Callback0& callback, std::string* value=0);
    void addChoice(CLIMenu& menu);
    void setExitString(const std::string& str);
    std::string title() const;
    void display();

  protected:
    unsigned int inputChoice(const std::string& text);

  private:
    struct Choice
    {
      Choice(const std::string& choicename,
             const Utilities::Callback0& callback, std::string* value);
      Choice(const Choice& copy);
      ~Choice();
      Choice& operator=(const Choice& rhs);

      std::string mChoicename;
      Utilities::Callback0* mCallback;
      std::string* mValue;
    };
    typedef std::vector<Choice> ChoiceList;

    std::string mTitle;
    std::string mExit;
    ChoiceList mChoices;
  };
}

#endif
