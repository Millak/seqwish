#include "paf.hpp"
#include "tokenize.hpp"

namespace seqwish {

paf_row_t::paf_row_t(const std::string& line) {
    std::vector<std::string> fields;
    tokenize(line, fields, " \t");
    query_sequence_name = fields[0];
    query_sequence_length = std::stoull(fields[1]);
    query_start = std::stoull(fields[2]);
    query_end = std::stoull(fields[3]);
    query_target_same_strand = (fields[4] == "+");
    target_sequence_name = fields[5];
    target_sequence_length = std::stoull(fields[6]);
    target_start = std::stoull(fields[7]);
    target_end = std::stoull(fields[8]);
    num_matches = std::stoull(fields[9]);
    alignment_block_length = std::stoull(fields[10]);
    mapping_quality = std::stoi(fields[11]);
    // find the cigar in the last fields
    for (size_t i = 12; i < fields.size(); ++i) {
        // cg:Z:
        auto& f = fields[i];
        //std::string::size_type n;
        auto n = f.find("cg:Z:");
        if (n == 0) {
            cigar = cigar_from_string(f.substr(5));
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const paf_row_t& pafrow) {
    out << pafrow.query_sequence_name << "\t"
        << pafrow.query_sequence_length << "\t"
        << pafrow.query_start << "\t"
        << pafrow.query_end << "\t"
        << (pafrow.query_target_same_strand?"+":"-") << "\t"
        << pafrow.target_sequence_name << "\t"
        << pafrow.target_sequence_length << "\t"
        << pafrow.target_start << "\t"
        << pafrow.target_end << "\t"
        << pafrow.num_matches << "\t"
        << pafrow.alignment_block_length << "\t"
        << pafrow.mapping_quality << "\t"
        << "cg:Z:" << cigar_to_string(pafrow.cigar);
    return out;
}

void dump_paf_alignments(const std::string& filename) {
    std::ifstream in(filename.c_str());
    std::string line;
    while (std::getline(in, line)) {
        paf_row_t pafrow(line);
        std::cout << pafrow << std::endl;
    }
}


std::vector<std::pair<std::string, uint64_t>> parse_paf_spec(const std::string& spec) {
    std::vector<std::pair<std::string, uint64_t>> parsed;
    std::vector<std::string> files;
    tokenize(spec, files, ",");
    for (auto& file : files) {
        std::vector<std::string> fields;
        tokenize(file, fields, ":");
        if (fields.size() == 2) {
            parsed.push_back(std::make_pair(fields.front(), std::stoull(fields.back())));
        } else if (fields.size() == 1) {
            parsed.push_back(std::make_pair(fields.front(), 0));
        }
    }
    return parsed;
}

}
