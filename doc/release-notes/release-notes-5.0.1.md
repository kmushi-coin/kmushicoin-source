KTV version v5.0.1 is now available from: https://github.com/ktv-project/ktv/releases
Please report bugs using the issue tracker at github: https://github.com/ktv-project/ktv/issues

Mandatory Update
----

This is an emergency update.
A vulnerability with the budgeting system was discovered and has been fixed (PR 2137).
This release also contains a protocol upgrade (to 70921).
Users will need to update their clients before enforcement of this update goes into effect.
Update enforcement is currently scheduled to go into effect at the same block height that was scheduled for v5.0.0: 2700500

Masternodes will need to be restarted once both the masternode daemon and the controller wallet have been upgraded.

Important Note
----

No user's funds are at risk, but users facing a checkpoint error after upgrade need to resync the chain.