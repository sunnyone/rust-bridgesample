extern crate gcc;
extern crate pkg_config;

use pkg_config::Config;

fn main() {
    // cf. 
    let mut config = Config::new();
    config.atleast_version("2.0");
    let library = config.probe("glib-2.0").unwrap();
    
    // cf. http://alexcrichton.com/pkg-config-rs/pkg_config/struct.Library.html
    for path in library.link_paths.iter() {
        println!("cargo:rustc-link-search=native={}", path.to_str().unwrap());
    }
    
    // cf. http://alexcrichton.com/gcc-rs/gcc/index.html
    let mut cc_config = gcc::Config::new();
    cc_config.file("src/bridge.c");
    for path in library.include_paths.iter() {
        cc_config.include(path);
    }
    
    cc_config.compile("libbridgesample.a");
}