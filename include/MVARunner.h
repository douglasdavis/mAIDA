#ifndef mAIDA_MVARunner_h
#define mAIDA_MVARunner_h

#include <vector>
#include <string>

namespace mAIDA {

  class MVARunner {

    std::string              _sig_file;
    std::string              _cut_file;
    std::string              _var_file;
    bool                     _wbe;
    std::vector<std::string> _bkg_files;
    std::vector<std::string> _methods;
    std::string              _out_file;
    
  public:

    MVARunner();
    virtual ~MVARunner();

    void Run();
    
    void set_sig_file(const std::string& sig_file);
    void set_cut_file(const std::string& cut_file);
    void set_var_file(const std::string& var_file);
    void add_bkg_file(const std::string& bkg_file);
    void set_out_file(const std::string& out_file);
    void add_method(const std::string& method);
    void set_wbe_true();
    
  };

}

inline void mAIDA::MVARunner::set_sig_file(const std::string& sig_file) { _sig_file = sig_file;           }
inline void mAIDA::MVARunner::set_cut_file(const std::string& cut_file) { _cut_file = cut_file;           }
inline void mAIDA::MVARunner::set_var_file(const std::string& var_file) { _var_file = var_file;           }
inline void mAIDA::MVARunner::add_bkg_file(const std::string& bkg_file) { _bkg_files.push_back(bkg_file); }
inline void mAIDA::MVARunner::set_out_file(const std::string& out_file) { _out_file = out_file;           }
inline void mAIDA::MVARunner::add_method(const std::string& method)     { _methods.push_back(method);     }
inline void mAIDA::MVARunner::set_wbe_true()                            { _wbe = true;                    }

#endif
