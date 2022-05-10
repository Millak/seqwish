#ifndef SEQINDEX_HPP_INCLUDED
#define SEQINDEX_HPP_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "sdsl/bit_vectors.hpp"
#include "sdsl/csa_wt.hpp"
#include "sdsl/suffix_arrays.hpp"
#include "sdsl/dac_vector.hpp"
#include "gzstream.h"
#include "pos.hpp"
#include "dna.hpp"

namespace seqwish {

class seqindex_t {

private:

    std::string basefilename;
    std::string seqfilename;
    std::string seqnamefile;
    std::string seqidxfile;
    size_t seq_count = 0;
    // a file containing the concatenated sequences
    //std::vector<std::ifstream> seqfiles;
    char* seq_buf;
    int seq_fd = 0;
    size_t seq_size = 0;
    void open_seq(const std::string& name);
    void close_seq(void);
    //std::ifstream& get_seqfile(void);
    // sequence offsets (for offset and length)
    sdsl::sd_vector<> seq_begin_cbv;
    sdsl::sd_vector<>::rank_1_type seq_begin_cbv_rank;
    sdsl::sd_vector<>::select_1_type seq_begin_cbv_select;
    // seq name compressed suffix array
    sdsl::csa_wt<> seq_name_csa;
    // seq name index
    sdsl::sd_vector<> seq_name_cbv;
    sdsl::sd_vector<>::rank_1_type seq_name_cbv_rank;
    sdsl::sd_vector<>::select_1_type seq_name_cbv_select;
    uint32_t OUTPUT_VERSION = 1; // update as we change our format

public:

    seqindex_t(void) { }
    ~seqindex_t(void) { close_seq(); }
    void set_base_filename();
    void build_index(const std::string& filename);
    size_t save(sdsl::structure_tree_node* s = NULL, const std::string& name = "");
    void load(const std::string& filename);
    void remove_index_files(void);
    void to_fasta(std::ostream& out, size_t linewidth = 60) const;
    std::string nth_name(size_t n) const;
    size_t rank_of_seq_named(const std::string& name) const;
    size_t nth_seq_length(size_t n) const;
    size_t nth_seq_offset(size_t n) const;
    std::string seq(const std::string& name) const;
    std::string subseq(const std::string& name, size_t pos, size_t count) const;
    std::string subseq(size_t n, size_t pos, size_t count) const;
    std::string subseq(size_t pos, size_t count) const;
    size_t pos_in_all_seqs(const std::string& name, size_t pos, bool is_rev) const;
    size_t pos_in_all_seqs(size_t n, size_t pos, bool is_rev) const;
    size_t seq_length(void) const;
    char at(size_t pos) const;
    char at_pos(pos_t pos) const;
    size_t n_seqs(void) const;
    size_t seq_id_at(size_t pos) const;
    bool seq_start(size_t pos) const;

};

}

#endif
