#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string& s, const string& delim) {
    vector<string> res;
    size_t pos = 0, end;
    while ((end = s.find(delim, pos)) != string::npos) {
        res.push_back(s.substr(pos, end - pos));
        pos = end + delim.length();
    }
    res.push_back(s.substr(pos));
    return res;
}

vector<string> parse_log(const string& line) {
    vector<string> res;
    size_t pos = 0;
    while (pos < line.length()) {
        while (pos < line.length() && isspace(line[pos])) pos++;
        if (pos >= line.length()) break;
        if (line[pos] == '"') {
            size_t end = line.find('"', pos + 1);
            if (end == string::npos) break;
            res.push_back(line.substr(pos + 1, end - pos - 1));
            pos = end + 1;
        } else if (line[pos] == '[') {
            size_t end = line.find(']', pos + 1);
            if (end == string::npos) break;
            res.push_back(line.substr(pos + 1, end - pos - 1));
            pos = end + 1;
        } else {
            size_t end = pos;
            while (end < line.length() && !isspace(line[end])) end++;
            res.push_back(line.substr(pos, end - pos));
            pos = end;
        }
    }
    return res;
}

int main() {
    string rules_line, desc_line;
    getline(cin, rules_line);
    getline(cin, desc_line);

    // Parse rules
    map<string, int> thresh;
    string clean_rules;
    for (char c : rules_line) if (!isspace(c)) clean_rules += c;
    vector<string> rule_parts = split(clean_rules, ",");
    for (const string& p : rule_parts) {
        if (p.empty()) continue;
        size_t eq = p.find('=');
        if (eq == string::npos) continue;
        string key = p.substr(0, eq);
        int val = stoi(p.substr(eq + 1));
        thresh[key] = val;
    }

    // Parse descriptor
    vector<string> field_names = split(desc_line, ", ");
    map<string, int> field_idx;
    for (int i = 0; i < field_names.size(); i++) {
        field_idx[field_names[i]] = i;
    }

    // Data structures
    struct DayData {
        set<string> agents, ips, sessions;
        int pdf_count = 0;
        vector<long long> pdf_ids;
    };
    map<string, map<string, DayData>> user_days;

    // Process logs
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        vector<string> vals = parse_log(line);
        if (vals.size() != field_names.size()) continue;

        string id = vals[field_idx["Id"]];
        if (id == "-") continue;

        string status = vals[field_idx["HTTP Status"]];
        if (status != "200") continue;

        string date_str = vals[field_idx["Date"]];
        size_t colon_pos = date_str.find(':');
        if (colon_pos == string::npos) continue;
        string day = date_str.substr(0, colon_pos);

        string ip = vals[field_idx["Client IP"]];
        string agent = vals[field_idx["User Agent"]];
        string session = vals[field_idx["Session Cookie"]];
        string request = vals[field_idx["Request"]];

        // Add to data
        DayData& dd = user_days[id][day];
        dd.agents.insert(agent);
        dd.ips.insert(ip);
        dd.sessions.insert(session);

        // Check if PDF
        if (request.find("GET /document/") == 0) {
            size_t start = string("GET /document/").length();
            size_t end = request.find(".pdf HTTP/1.1");
            if (end != string::npos && end > start) {
                string id_str = request.substr(start, end - start);
                bool is_num = true;
                for (char c : id_str) if (!isdigit(c)) { is_num = false; break; }
                if (is_num) {
                    long long pdf_id = stoll(id_str);
                    dd.pdf_count++;
                    dd.pdf_ids.push_back(pdf_id);
                }
            }
        }
    }

    // Compute violations
    map<string, map<string, int>> all_vios;
    for (auto& user_pair : user_days) {
        const string& uid = user_pair.first;
        map<string, int> violations;
        for (auto& day_pair : user_pair.second) {
            const DayData& dd = day_pair.second;

            // agent
            int num_agents = dd.agents.size();
            if (thresh.count("agent") && num_agents >= thresh["agent"]) {
                violations["agent"] = num_agents;
            }

            // ip
            int num_ips = dd.ips.size();
            if (thresh.count("ip") && num_ips >= thresh["ip"]) {
                violations["ip"] = num_ips;
            }

            // session
            int num_sessions = dd.sessions.size();
            if (thresh.count("session") && num_sessions >= thresh["session"]) {
                violations["session"] = num_sessions;
            }

            // pdf
            if (thresh.count("pdf") && dd.pdf_count >= thresh["pdf"]) {
                violations["pdf"] = dd.pdf_count;
            }

            // crawl
            if (thresh.count("crawl") && !dd.pdf_ids.empty()) {
                int max_streak = 1;
                int current = 1;
                for (size_t i = 1; i < dd.pdf_ids.size(); ++i) {
                    if (dd.pdf_ids[i] == dd.pdf_ids[i - 1] + 1) {
                        current++;
                        max_streak = max(max_streak, current);
                    } else {
                        current = 1;
                    }
                }
                if (max_streak >= thresh["crawl"]) {
                    violations["crawl"] = max_streak;
                }
            }
        }
        if (!violations.empty()) {
            all_vios[uid] = violations;
        }
    }

    // Output
    if (all_vios.empty()) {
        cout << "N/A" << endl;
    } else {
        for (const auto& u : all_vios) {
            for (const auto& t : u.second) {
                cout << u.first << " " << t.first << "=" << t.second << endl;
            }
        }
    }

    return 0;
}