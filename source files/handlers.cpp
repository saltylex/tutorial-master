#include "../header files/handlers.h"
#include <fstream>

void CSVHandler::save(const std::vector<Tutorial> v) {
    std::ofstream out("watchlist.csv");

    for(const Tutorial& t : v) {
        out << t.get_title() << ",";
        out << t.get_presenter() << ",";
        out << t.get_duration().minutes << ":";
        if(t.get_duration().seconds>9)
        out << t.get_duration().seconds << ",";
        else
            out <<"0"<< t.get_duration().seconds << ",";
        out << t.get_likes() << ",";
        out << t.get_link() << "\n";
    }
    out.close();
}

#include <fstream>

void HTMLHandler::save(const std::vector<Tutorial> v) {
    std::ofstream out("watchlist.html");
    out << "<!DOCTYPE html><html><head><title>Watch List</title><style>table, th, td {\n"
           "  border: 1px solid;\n"
           "}</style></head><body><table>";
    out << "        <tr>\n"
           "            <td>Title</td>\n"
           "            <td>Presenter</td>\n"
           "            <td>Duration</td>\n"
           "            <td>Likes</td>\n"
           "            <td>Link</td>\n"
           "        </tr>";
    for (const Tutorial &t: v) {
        out << "<tr>";

        out << "<td>" << t.get_title() << "</td>";
        out << "<td>" << t.get_presenter() << "</td>";
        if(t.get_duration().seconds>9)
        out << "<td>" << t.get_duration().minutes<<":"<<t.get_duration().seconds << "</td>";
        else
            out << "<td>" << t.get_duration().minutes<<":0"<<t.get_duration().seconds << "</td>";
        out << "<td>" << t.get_likes() << "</td>";
        out << "<td><a href=\"" << t.get_link() << "\">LINK</a></td>";

        out << "</tr>";
    }
    out << "</table></body></html>";
    out.close();
}