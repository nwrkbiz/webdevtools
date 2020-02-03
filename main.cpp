/**
 * @file main.cpp
 * @brief Program entry point.
 * @author Daniel Giritzer
 * @copyright "THE BEER-WARE LICENSE" (Revision 42):
 * <giri@nwrk.biz> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Daniel Giritzer
 */
#include <iostream>
#include <FL/fl_ask.H>
#include "View.h"

using namespace giri;

int main(int argc, char *argv[]){
    try
    {
        View::SPtr view {std::make_shared<View>()};
        return Fl::run();
    }
    catch(const ExceptionBase& e)
    {
        std::cerr << e.getMessage() << std::endl;
        fl_alert(e.getMessage().c_str());
        return EXIT_FAILURE;
    }
    catch (std::bad_alloc const& e)
    {
        std::cerr << "Exeption Caught: Bad memory allocation ( " << e.what() << " )" << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unhandled exeption caught!" << std::endl;
        return EXIT_FAILURE;
    }
}