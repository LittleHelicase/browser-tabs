{
  'targets': [
    {
      'target_name': 'chromeTabs',
      'cflags': ['-std=c++0x'],
      'xcode_settings': {
        'OTHER_CFLAGS': [ '-stdlib=libc++','-mmacosx-version-min=10.7','-std=c++0x' ]
      },
      'include_dirs': [
        'chromeTabs/SNSS-Parser/includes',
      ],
      'sources': [
        'chromeTabs/SNSS-Parser/SNSSParser.cpp',
        'chromeTabs/binding.cpp',
        'chromeTabs/src/chrome_open_tabs.cpp',
        'chromeTabs/src/util/home_dir.cpp',
      ],
    },
  ],
}
