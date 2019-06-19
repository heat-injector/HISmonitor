# HISmonitor
AssetTracker with Data Collection
These files are shared by particle.io as an example of features the Asset Tracker offers.

-Log Running Hours (start and stop time) and report to a central database.

-Disable/Enable the Run Sequence on the Machine with an external signal and automated action by reading a field in a table which we would load if payments aren’t received on time and clear the “stop operations” field in the central database when current.

-When charge status is initialized - PUT the GPS coordinates + Battery health on the central database and GET “stop operation”  from the central database (this starts a new job, Void if interval is less than 10 minutes because it is the same job)

-Each Machine would have its own “table” on the central database (GoogleDrive API).  The GPS location starts a new job in the job table.
