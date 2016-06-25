#include "include/slacking/slacking.hpp"

#include <fstream>

int main() {
        slack::create("xoxb-48165358327-Lfrjl7FuQB0NeyaD5LdtEAHK");
    

    {
        // Calling API method is easy with some chosen free function
        slack::api().test();
        // Or if you prefer you can take back the instance reference and use member function
        auto& slack = slack::instance();
        slack.api.test();
        // Helper member and free functions have the same signature
    }

    {
        // Get the instance and fill some permanent chat_postMessage parameters
        auto& slack = slack::instance();
        slack.chat.channel = "#mychannel"; // required
        slack.chat.username = "botname";   // optional check the doc

        slack.chat.postMessage("Hello there! Visit https://api.slack.com !");
    }

    {
        // We don't always have to store a reference
        slack::instance().chat.parse = "full"; // see https://api.slack.com/docs/formatting for more information
        // slack::chat().parse = "full"; // alternative equivalent helper function

        // Note that Slacking remembers the chat_postMessage parameters
        // Here we just change the as_user parameter permanently
        slack::chat().as_user = true; // see as_user documentation it will override username here

        // We can also send via helper free function
        slack::chat().postMessage("Hello @bob please join #general!");

        try {
            slack::instance().chat.postMessage("Hello there in another chanel!", "#otherchannel");
        }
        catch(std::exception const& e) {
            std::cerr << "channel might not exist: " << e.what() << '\n'; // yep we can try/catch slacking methods
        }
    }

    {
        auto users = slack::users().list();
        std::cout << users.dump(2) << '\n'; // will display users list information
    }

}
