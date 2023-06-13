int timeToInt(std::string s) {
    int hh = std::stoi(s.substr(0, 2));
    int mm = std::stoi(s.substr(3));
    return hh * 60 + mm;
}

std::string intToTime(int x) {
    int hh = x / 60;
    int mm = x % 60;
    std::string s;
    s += '0' + hh / 10;
    s += '0' + hh % 10;
    s += ':';
    s += '0' + mm / 10;
    s += '0' + mm % 10;
    return s;
}