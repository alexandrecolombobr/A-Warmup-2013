/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Library General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Shoe class
class Shoe {

public:

    Shoe() {}

    Shoe(const auto size, const auto foot)
        : m_size(size)
        , m_rightFoot(foot)
    {}

    inline void setSize (const auto value) {
        m_size = value;
    }

    inline void setFoot (const auto value) {
        m_rightFoot = value;
    }

    inline const auto getSize () {
        return m_size;
    }

    inline const auto getFoot () {
        return m_rightFoot;
    }

    inline static const auto translateFoot( const std::string &foot ) {
        if (foot == "D")
            return true;
        else
            return false;
    }

private:
    int m_size = 30;
    bool m_rightFoot = false;
};

// Main function
int main(int argc, char *argv[])
{
    (void)argc;
    std::fstream in(argv[1]);

    auto firstLine = true;
    auto amountOfPairs = 0;
    std::string line;
    std::vector<Shoe*> myShoes;

    // Reading file
    while ( std::getline(in, line) ) {
        // Ignore first line
        if (firstLine) {
            firstLine = false;
        }
        // Iterate over shoes
        else {
            std::string buffer;
            std::stringstream ss(line);
            std::vector<std::string> tokens;
            bool pairFound = false;
            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            // Do I have the other foot?
            for ( std::vector<Shoe*>::iterator it = myShoes.begin(); it != myShoes.end(); ) {
                if ( !pairFound
                     && myShoes.at(std::distance(myShoes.begin(), it))->getSize() == std::stoi(tokens.at(0))
                     && myShoes.at(std::distance(myShoes.begin(), it))->getFoot() == !Shoe::translateFoot(tokens.at(1)) ) {
                    myShoes.erase(it);
                    pairFound = true;
                    amountOfPairs++;
                }
                else {
                    ++it;
                }
            }
            // No
            if ( !pairFound )
                myShoes.push_back( new Shoe( std::stoi(tokens.at(0)), Shoe::translateFoot(tokens.at(1)) ) );
        }
    }
    // Show amount of pairs found
    std::cout << amountOfPairs;
}
