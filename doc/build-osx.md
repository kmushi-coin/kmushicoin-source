macOS Build Instructions and Notes
====================================
The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

Preparation
-----------
Install the macOS command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

Dependencies
----------------------

    brew install autoconf automake berkeley-db4 libtool boost miniupnpc libnatpmp pkg-config python3 qt5 zmq libevent qrencode gmp libsodium rust

See [dependencies.md](dependencies.md) for a complete overview.

If you want to build the disk image with `make deploy` (.dmg / optional), you need RSVG:

    brew install librsvg

and [`macdeployqtplus`](../contrib/macdeploy/README.md) dependencies:
```shell
pip3 install ds_store mac_alias
```

Berkeley DB
-----------
It is recommended to use Berkeley DB 4.8. If you have to build it yourself,
you can use [the installation script included in contrib/](/contrib/install_db4.sh)
like so:

```shell
./contrib/install_db4.sh .
```

from the root of the repository.

**Note**: You only need Berkeley DB if the wallet is enabled (see [*Disable-wallet mode*](/doc/build-osx.md#disable-wallet-mode)).

Build KTV Core
------------------------

1. Clone the KTV Core source code:

        git clone https://github.com/kmushi-coin/kmushicoin-source
        cd ktv

2.  Build KTV Core:

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        ./params/install-params.sh
        make check

4.  You can also create a .dmg that contains the .app bundle (optional):

        make deploy

Disable-wallet mode
--------------------
**Note:** This functionality is not yet completely implemented, and compilation using the below option will currently fail.

When the intention is to run only a P2P node without a wallet, KTV Core may be compiled in
disable-wallet mode with:

    ./configure --disable-wallet

In this case there is no dependency on Berkeley DB 4.8.

Running
-------

KTV Core is now available at `./src/ktvd`

Before running, you may create an empty configuration file:

    mkdir -p "/Users/${USER}/Library/Application Support/KTV"

    touch "/Users/${USER}/Library/Application Support/KTV/ktv.conf"

    chmod 600 "/Users/${USER}/Library/Application Support/KTV/ktv.conf"

The first time you run ktvd, it will start downloading the blockchain. This process could take many hours, or even days on slower than average systems.

You can monitor the download process by looking at the debug.log file:

    tail -f $HOME/Library/Application\ Support/KTV/debug.log

Other commands:
-------

    ./src/ktvd -daemon # Starts the ktv daemon.
    ./src/ktv-cli --help # Outputs a list of command-line options.
    ./src/ktv-cli help # Outputs a list of RPC commands when the daemon is running.

Notes
-----

* Tested on OS X 10.12 Sierra through macOS 10.15 Catalina on 64-bit Intel processors only.

* Building with downloaded Qt binaries is not officially supported. See the notes in [#7714](https://github.com/bitcoin/bitcoin/issues/7714)
