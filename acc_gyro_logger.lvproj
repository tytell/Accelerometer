<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="12008004">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Old" Type="Folder">
			<Item Name="acc_gyro to waveform.vi" Type="VI" URL="../acc_gyro to waveform.vi"/>
			<Item Name="acc_gyro_data.ctl" Type="VI" URL="../acc_gyro_data.ctl"/>
			<Item Name="acc_gyro_enc to waveform.vi" Type="VI" URL="../acc_gyro_enc to waveform.vi"/>
			<Item Name="acc_gyro_enc_logger.vi" Type="VI" URL="../acc_gyro_enc_logger.vi"/>
			<Item Name="acc_gyro_logger.vi" Type="VI" URL="../acc_gyro_logger.vi"/>
			<Item Name="acc_gyro_motor_logger.vi" Type="VI" URL="../acc_gyro_motor_logger.vi"/>
			<Item Name="data to acc_gyro.vi" Type="VI" URL="../data to acc_gyro.vi"/>
			<Item Name="data to selftest.vi" Type="VI" URL="../data to selftest.vi"/>
			<Item Name="get selftest.vi" Type="VI" URL="../get selftest.vi"/>
			<Item Name="ignore some errors.vi" Type="VI" URL="../ignore some errors.vi"/>
			<Item Name="read_serial_check.vi" Type="VI" URL="../read_serial_check.vi"/>
			<Item Name="selftest_data.ctl" Type="VI" URL="../selftest_data.ctl"/>
		</Item>
		<Item Name="Test" Type="Folder">
			<Item Name="Test Read Accelerometer.vi" Type="VI" URL="../Test Read Accelerometer.vi"/>
			<Item Name="TestI2C.vi" Type="VI" URL="../TestI2C.vi"/>
			<Item Name="View TDMS File.vi" Type="VI" URL="../View TDMS File.vi"/>
		</Item>
		<Item Name="Accelerometer Data to Waveform.vi" Type="VI" URL="../Accelerometer Data to Waveform.vi"/>
		<Item Name="Accelerometer Data.ctl" Type="VI" URL="../Accelerometer Data.ctl"/>
		<Item Name="Accelerometer Logger.vi" Type="VI" URL="../Accelerometer Logger.vi"/>
		<Item Name="Accelerometer.ctl" Type="VI" URL="../Accelerometer.ctl"/>
		<Item Name="AccelerometerSPI.ctl" Type="VI" URL="../AccelerometerSPI.ctl"/>
		<Item Name="Close Accelerometer SPI.vi" Type="VI" URL="../Close Accelerometer SPI.vi"/>
		<Item Name="Close Accelerometer.vi" Type="VI" URL="../Close Accelerometer.vi"/>
		<Item Name="Configure Accelerometer SPI.vi" Type="VI" URL="../Configure Accelerometer SPI.vi"/>
		<Item Name="Configure Accelerometer.vi" Type="VI" URL="../Configure Accelerometer.vi"/>
		<Item Name="continue file.vi" Type="VI" URL="../continue file.vi"/>
		<Item Name="increment file name.vi" Type="VI" URL="../increment file name.vi"/>
		<Item Name="Open Accelerometer SPI.vi" Type="VI" URL="../Open Accelerometer SPI.vi"/>
		<Item Name="Open Accelerometer.vi" Type="VI" URL="../Open Accelerometer.vi"/>
		<Item Name="Read Accelerometer SPI.vi" Type="VI" URL="../Read Accelerometer SPI.vi"/>
		<Item Name="Read Accelerometer.vi" Type="VI" URL="../Read Accelerometer.vi"/>
		<Item Name="Save Accelerometer Data.vi" Type="VI" URL="../Save Accelerometer Data.vi"/>
		<Item Name="Set Accel Time.vi" Type="VI" URL="../Set Accel Time.vi"/>
		<Item Name="setup file.vi" Type="VI" URL="../setup file.vi"/>
		<Item Name="SPI read.vi" Type="VI" URL="../SPI read.vi"/>
		<Item Name="test jitter.vi" Type="VI" URL="../test jitter.vi"/>
		<Item Name="Test read SPI.vi" Type="VI" URL="../Test read SPI.vi"/>
		<Item Name="time jitter.vi" Type="VI" URL="../time jitter.vi"/>
		<Item Name="Zero Accelerometer.vi" Type="VI" URL="../Zero Accelerometer.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="AsciiToInt.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/AsciiToInt.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="ClearError.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/ClearError.vi"/>
				<Item Name="configureNumberOfValues.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/configureNumberOfValues.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="ExtractSubstring.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/ExtractSubstring.vi"/>
				<Item Name="fileViewerConfigData.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/fileViewerConfigData.ctl"/>
				<Item Name="formatPropertyList.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/formatPropertyList.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="Get Type of Variant.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Get Type of Variant.vi"/>
				<Item Name="getChannelList.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/getChannelList.vi"/>
				<Item Name="getNamesFromPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/getNamesFromPath.vi"/>
				<Item Name="initFileContentsTree.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/initFileContentsTree.vi"/>
				<Item Name="initHelpButtonVisibility.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/initHelpButtonVisibility.vi"/>
				<Item Name="initTabValues.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/initTabValues.vi"/>
				<Item Name="loadAndFormatValues.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/loadAndFormatValues.vi"/>
				<Item Name="LogicalSort.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/LogicalSort.vi"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="LVRowAndColumnUnsignedTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRowAndColumnUnsignedTypeDef.ctl"/>
				<Item Name="NI-845x Close Device Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x Close Device Reference.vi"/>
				<Item Name="NI-845x Close Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x Close Reference.vi"/>
				<Item Name="NI-845x DIO Read Line.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x DIO Read Line.vi"/>
				<Item Name="NI-845x Fill in Error Info.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x Fill in Error Info.vi"/>
				<Item Name="NI-845x I2C Close Configuration Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x I2C Close Configuration Reference.vi"/>
				<Item Name="NI-845x I2C Close Script Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x I2C Close Script Reference.vi"/>
				<Item Name="NI-845x I2C Create Configuration Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x I2C Create Configuration Reference.vi"/>
				<Item Name="NI-845x I2C Slave Close Configuration Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x I2C Slave Close Configuration Reference.vi"/>
				<Item Name="NI-845x I2C Write Read.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x I2C Write Read.vi"/>
				<Item Name="NI-845x I2C Write.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x I2C Write.vi"/>
				<Item Name="NI-845x SPI Close Configuration Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x SPI Close Configuration Reference.vi"/>
				<Item Name="NI-845x SPI Close Script Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x SPI Close Script Reference.vi"/>
				<Item Name="NI-845x SPI Create Configuration Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x SPI Create Configuration Reference.vi"/>
				<Item Name="NI-845x SPI Stream Close Configuration Reference.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x SPI Stream Close Configuration Reference.vi"/>
				<Item Name="NI-845x SPI Write Read.vi" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/NI-845x SPI Write Read.vi"/>
				<Item Name="ni845xControl.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xControl.ctl"/>
				<Item Name="ni845xDioLineWriteValue.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xDioLineWriteValue.ctl"/>
				<Item Name="ni845xI2cConfiguration.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xI2cConfiguration.ctl"/>
				<Item Name="ni845xI2cScriptControl.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xI2cScriptControl.ctl"/>
				<Item Name="ni845xI2cSlaveConfiguration.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xI2cSlaveConfiguration.ctl"/>
				<Item Name="ni845xSpiConfiguration.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xSpiConfiguration.ctl"/>
				<Item Name="ni845xSpiScriptControl.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xSpiScriptControl.ctl"/>
				<Item Name="ni845xSpiStreamConfiguration.ctl" Type="VI" URL="/&lt;vilib&gt;/ni845x/ni845x.llb/ni845xSpiStreamConfiguration.ctl"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_Gmath.lvlib" Type="Library" URL="/&lt;vilib&gt;/gmath/NI_Gmath.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="panelResize.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/panelResize.vi"/>
				<Item Name="setListBoxColumnWidths.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/setListBoxColumnWidths.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="status.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/status.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="TDMS - File Viewer.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/TDMS - File Viewer.vi"/>
				<Item Name="TDMSFileViewer_LaunchHelp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/TDMSFileViewer_LaunchHelp.vi"/>
				<Item Name="TDMSFileViewerLocalizedText.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/TDMSFileViewerLocalizedText.vi"/>
				<Item Name="Type Enum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Type Enum.ctl"/>
				<Item Name="VariantType to Type Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/VariantType to Type Code.vi"/>
				<Item Name="VariantType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/VariantDataType/VariantType.lvlib"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
			<Item Name="acc_gyro_enc_data.ctl" Type="VI" URL="../acc_gyro_enc_data.ctl"/>
			<Item Name="acc_gyro_sync_data.ctl" Type="VI" URL="../acc_gyro_sync_data.ctl"/>
			<Item Name="data to acc_gyro_enc.vi" Type="VI" URL="../data to acc_gyro_enc.vi"/>
			<Item Name="data to acc_gyro_sync.vi" Type="VI" URL="../data to acc_gyro_sync.vi"/>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="ni845x.dll" Type="Document" URL="ni845x.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
