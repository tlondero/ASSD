#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Simulation G3
# GNU Radio version: 3.7.13.5
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from PyQt4.QtCore import QObject, pyqtSlot
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.qtgui import Range, RangeWidget
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import epy_module_0  # embedded python module
import sip
import sys
from gnuradio import qtgui


class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Simulation G3")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Simulation G3")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())


        ##################################################
        # Variables
        ##################################################
        self.variable_qtgui_chooser_0 = variable_qtgui_chooser_0 = 0
        self.samplenholdcheck = samplenholdcheck = True
        self.samp_rate = samp_rate = 300000
        self.m = m = 0.5
        self.llaveAnalcheck = llaveAnalcheck = True
        self.fportadora = fportadora = 3000
        self.fp = fp = 10500
        self.fmoduladora = fmoduladora = 300
        self.faacheck = faacheck = True
        self.dutycycle = dutycycle = 0.5
        self.UIF = UIF = 1500
        self.SR = SR = 20000
        self.FR = FR = True
        self.AMPLITUD = AMPLITUD = 1

        ##################################################
        # Blocks
        ##################################################
        self._variable_qtgui_chooser_0_options = (0, 1, 2, 3, )
        self._variable_qtgui_chooser_0_labels = ('Sine', 'Triangle', 'SIN3/2', 'AM', )
        self._variable_qtgui_chooser_0_tool_bar = Qt.QToolBar(self)
        self._variable_qtgui_chooser_0_tool_bar.addWidget(Qt.QLabel('Signal'+": "))
        self._variable_qtgui_chooser_0_combo_box = Qt.QComboBox()
        self._variable_qtgui_chooser_0_tool_bar.addWidget(self._variable_qtgui_chooser_0_combo_box)
        for label in self._variable_qtgui_chooser_0_labels: self._variable_qtgui_chooser_0_combo_box.addItem(label)
        self._variable_qtgui_chooser_0_callback = lambda i: Qt.QMetaObject.invokeMethod(self._variable_qtgui_chooser_0_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._variable_qtgui_chooser_0_options.index(i)))
        self._variable_qtgui_chooser_0_callback(self.variable_qtgui_chooser_0)
        self._variable_qtgui_chooser_0_combo_box.currentIndexChanged.connect(
        	lambda i: self.set_variable_qtgui_chooser_0(self._variable_qtgui_chooser_0_options[i]))
        self.top_grid_layout.addWidget(self._variable_qtgui_chooser_0_tool_bar, 0, 0, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        _samplenholdcheck_check_box = Qt.QCheckBox('Sample and Hold')
        self._samplenholdcheck_choices = {True: True, False: False}
        self._samplenholdcheck_choices_inv = dict((v,k) for k,v in self._samplenholdcheck_choices.iteritems())
        self._samplenholdcheck_callback = lambda i: Qt.QMetaObject.invokeMethod(_samplenholdcheck_check_box, "setChecked", Qt.Q_ARG("bool", self._samplenholdcheck_choices_inv[i]))
        self._samplenholdcheck_callback(self.samplenholdcheck)
        _samplenholdcheck_check_box.stateChanged.connect(lambda i: self.set_samplenholdcheck(self._samplenholdcheck_choices[bool(i)]))
        self.top_grid_layout.addWidget(_samplenholdcheck_check_box, 2, 0, 1, 1)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._m_range = Range(0, 1, 0.05, 0.5, 200)
        self._m_win = RangeWidget(self._m_range, self.set_m, 'Modulation coefficient', "counter", float)
        self.top_grid_layout.addWidget(self._m_win, 5, 4, 1, 1)
        for r in range(5, 6):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        _llaveAnalcheck_check_box = Qt.QCheckBox('Analog Switch')
        self._llaveAnalcheck_choices = {True: True, False: False}
        self._llaveAnalcheck_choices_inv = dict((v,k) for k,v in self._llaveAnalcheck_choices.iteritems())
        self._llaveAnalcheck_callback = lambda i: Qt.QMetaObject.invokeMethod(_llaveAnalcheck_check_box, "setChecked", Qt.Q_ARG("bool", self._llaveAnalcheck_choices_inv[i]))
        self._llaveAnalcheck_callback(self.llaveAnalcheck)
        _llaveAnalcheck_check_box.stateChanged.connect(lambda i: self.set_llaveAnalcheck(self._llaveAnalcheck_choices[bool(i)]))
        self.top_grid_layout.addWidget(_llaveAnalcheck_check_box, 3, 0, 1, 1)
        for r in range(3, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._fportadora_range = Range(500, 3000, 100, 3000, 200)
        self._fportadora_win = RangeWidget(self._fportadora_range, self.set_fportadora, 'Carrier frequency', "counter_slider", float)
        self.top_grid_layout.addWidget(self._fportadora_win, 4, 4, 1, 1)
        for r in range(4, 5):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._fmoduladora_range = Range(1, 500, 10, 300, 200)
        self._fmoduladora_win = RangeWidget(self._fmoduladora_range, self.set_fmoduladora, 'Modulator frequency', "counter_slider", float)
        self.top_grid_layout.addWidget(self._fmoduladora_win, 3, 4, 1, 1)
        for r in range(3, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        _faacheck_check_box = Qt.QCheckBox('Anti-Alias Filter')
        self._faacheck_choices = {True: True, False: False}
        self._faacheck_choices_inv = dict((v,k) for k,v in self._faacheck_choices.iteritems())
        self._faacheck_callback = lambda i: Qt.QMetaObject.invokeMethod(_faacheck_check_box, "setChecked", Qt.Q_ARG("bool", self._faacheck_choices_inv[i]))
        self._faacheck_callback(self.faacheck)
        _faacheck_check_box.stateChanged.connect(lambda i: self.set_faacheck(self._faacheck_choices[bool(i)]))
        self.top_grid_layout.addWidget(_faacheck_check_box, 1, 0, 1, 1)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._dutycycle_range = Range(0.05, 0.95, 0.05, 0.5, 50)
        self._dutycycle_win = RangeWidget(self._dutycycle_range, self.set_dutycycle, 'Duty cycle', "counter_slider", float)
        self.top_grid_layout.addWidget(self._dutycycle_win, 0, 1, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._UIF_range = Range(100, 5000, 10, 1500, 200)
        self._UIF_win = RangeWidget(self._UIF_range, self.set_UIF, 'Frequency', "counter_slider", float)
        self.top_grid_layout.addWidget(self._UIF_win, 3, 1, 2, 3)
        for r in range(3, 5):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._SR_range = Range(100, 50000, 100, 20000, 200)
        self._SR_win = RangeWidget(self._SR_range, self.set_SR, 'Sample Rate', "counter_slider", float)
        self.top_grid_layout.addWidget(self._SR_win, 1, 1, 2, 3)
        for r in range(1, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        _FR_check_box = Qt.QCheckBox('Recover Filter')
        self._FR_choices = {True: True, False: False}
        self._FR_choices_inv = dict((v,k) for k,v in self._FR_choices.iteritems())
        self._FR_callback = lambda i: Qt.QMetaObject.invokeMethod(_FR_check_box, "setChecked", Qt.Q_ARG("bool", self._FR_choices_inv[i]))
        self._FR_callback(self.FR)
        _FR_check_box.stateChanged.connect(lambda i: self.set_FR(self._FR_choices[bool(i)]))
        self.top_grid_layout.addWidget(_FR_check_box, 4, 0, 1, 1)
        for r in range(4, 5):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._AMPLITUD_range = Range(1, 15, 1, 1, 200)
        self._AMPLITUD_win = RangeWidget(self._AMPLITUD_range, self.set_AMPLITUD, 'Amplitude', "counter", float)
        self.top_grid_layout.addWidget(self._AMPLITUD_win, 0, 3, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(3, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.sen32 = blocks.wavfile_source('sen32.wav', True)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
        	1024, #size
        	samp_rate, #samp_rate
        	"", #name
        	5 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(-1, False)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_AUTO, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(True)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)

        if not True:
          self.qtgui_time_sink_x_0.disable_legend()

        labels = ['Input', 'AAF', 'Sample and Hold', 'Analog Switch', 'RF',
                  'poronga', 'Poronga Char', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in xrange(5):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_win, 6, 0, 1, 4)
        for r in range(6, 7):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_f(
        	1024, #size
        	firdes.WIN_BLACKMAN_hARRIS, #wintype
        	0, #fc
        	samp_rate, #bw
        	"", #name
        	5 #number of inputs
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(True)

        if not True:
          self.qtgui_freq_sink_x_0.disable_legend()

        if "float" == "float" or "float" == "msg_float":
          self.qtgui_freq_sink_x_0.set_plot_pos_half(not True)

        labels = ['Input', 'AAF', 'Sample and Hold', 'Analog Switch', 'FR',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "cyan", "yellow",
                  "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(5):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_freq_sink_x_0_win, 8, 0, 1, 4)
        for r in range(8, 9):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.low_pass_filter_0 = filter.interp_fir_filter_fff(1, firdes.low_pass(
        	1, samp_rate, fp, 2500, firdes.WIN_HAMMING, 6.76))
        self.filtro_antialiasing = filter.fir_filter_fff(1, firdes.low_pass(
        	1, samp_rate, fp, 2500, firdes.WIN_HAMMING, 6.76))
        self.blocks_throttle_0_0_0 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.blocks_throttle_0_0 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.blocks_threshold_ff_0 = blocks.threshold_ff(1-dutycycle, 1-dutycycle, 0)
        self.blocks_sample_and_hold_xx_0 = blocks.sample_and_hold_ff()
        self.blocks_multiply_xx_0 = blocks.multiply_vff(1)
        self.blocks_multiply_const_vxx_0_2 = blocks.multiply_const_vff((AMPLITUD, ))
        self.blocks_multiply_const_vxx_0_1_0 = blocks.multiply_const_vff((-1, ))
        self.blocks_multiply_const_vxx_0_1 = blocks.multiply_const_vff((m/2, ))
        self.blocks_multiply_const_vxx_0_0 = blocks.multiply_const_vff((m/2, ))
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff((2, ))
        self.blocks_float_to_char_0_2 = blocks.float_to_char(1, 1)
        self.blocks_add_xx_0 = blocks.add_vff(1)
        self.blocks_add_const_vxx_0 = blocks.add_const_vff((1, ))
        self.blks2_selector_0_1_0_0_0_0 = grc_blks2.selector(
        	item_size=gr.sizeof_float*1,
        	num_inputs=2,
        	num_outputs=1,
        	input_index=FR,
        	output_index=0,
        )
        self.blks2_selector_0_1_0_0_0 = grc_blks2.selector(
        	item_size=gr.sizeof_float*1,
        	num_inputs=2,
        	num_outputs=1,
        	input_index=llaveAnalcheck,
        	output_index=0,
        )
        self.blks2_selector_0_1_0_0 = grc_blks2.selector(
        	item_size=gr.sizeof_float*1,
        	num_inputs=2,
        	num_outputs=1,
        	input_index=samplenholdcheck,
        	output_index=0,
        )
        self.blks2_selector_0_1_0 = grc_blks2.selector(
        	item_size=gr.sizeof_float*1,
        	num_inputs=2,
        	num_outputs=1,
        	input_index=faacheck,
        	output_index=0,
        )
        self.blks2_selector_0_1 = grc_blks2.selector(
        	item_size=gr.sizeof_float*1,
        	num_inputs=4,
        	num_outputs=1,
        	input_index=variable_qtgui_chooser_0,
        	output_index=0,
        )
        self.analog_sig_source_x_0_2_1 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, fportadora-fmoduladora, AMPLITUD, 0)
        self.analog_sig_source_x_0_2_0 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, fportadora + fmoduladora, AMPLITUD, 0)
        self.analog_sig_source_x_0_2 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, fportadora, AMPLITUD, 0)
        self.analog_sig_source_x_0_0_0_0 = analog.sig_source_f(samp_rate, analog.GR_SAW_WAVE, SR, 1, 0)
        self.analog_sig_source_x_0_0 = analog.sig_source_f(samp_rate, analog.GR_TRI_WAVE, UIF, AMPLITUD, -AMPLITUD/2)
        self.analog_sig_source_x_0 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, UIF, AMPLITUD, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.blks2_selector_0_1, 0))
        self.connect((self.analog_sig_source_x_0_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.analog_sig_source_x_0_0_0_0, 0), (self.blocks_threshold_ff_0, 0))
        self.connect((self.analog_sig_source_x_0_2, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.analog_sig_source_x_0_2_0, 0), (self.blocks_multiply_const_vxx_0_0, 0))
        self.connect((self.analog_sig_source_x_0_2_1, 0), (self.blocks_multiply_const_vxx_0_1, 0))
        self.connect((self.blks2_selector_0_1, 0), (self.blks2_selector_0_1_0, 0))
        self.connect((self.blks2_selector_0_1, 0), (self.filtro_antialiasing, 0))
        self.connect((self.blks2_selector_0_1, 0), (self.qtgui_freq_sink_x_0, 0))
        self.connect((self.blks2_selector_0_1, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blks2_selector_0_1_0, 0), (self.blocks_throttle_0_0, 0))
        self.connect((self.blks2_selector_0_1_0_0, 0), (self.blks2_selector_0_1_0_0_0, 0))
        self.connect((self.blks2_selector_0_1_0_0, 0), (self.blocks_throttle_0_0_0, 0))
        self.connect((self.blks2_selector_0_1_0_0_0, 0), (self.blks2_selector_0_1_0_0_0_0, 0))
        self.connect((self.blks2_selector_0_1_0_0_0, 0), (self.low_pass_filter_0, 0))
        self.connect((self.blks2_selector_0_1_0_0_0, 0), (self.qtgui_freq_sink_x_0, 3))
        self.connect((self.blks2_selector_0_1_0_0_0, 0), (self.qtgui_time_sink_x_0, 3))
        self.connect((self.blks2_selector_0_1_0_0_0_0, 0), (self.qtgui_freq_sink_x_0, 4))
        self.connect((self.blks2_selector_0_1_0_0_0_0, 0), (self.qtgui_time_sink_x_0, 4))
        self.connect((self.blocks_add_const_vxx_0, 0), (self.blocks_float_to_char_0_2, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.blks2_selector_0_1, 3))
        self.connect((self.blocks_float_to_char_0_2, 0), (self.blocks_sample_and_hold_xx_0, 1))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.blks2_selector_0_1, 1))
        self.connect((self.blocks_multiply_const_vxx_0_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_multiply_const_vxx_0_1, 0), (self.blocks_add_xx_0, 2))
        self.connect((self.blocks_multiply_const_vxx_0_1_0, 0), (self.blocks_add_const_vxx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0_2, 0), (self.blks2_selector_0_1, 2))
        self.connect((self.blocks_multiply_xx_0, 0), (self.blks2_selector_0_1_0_0_0, 1))
        self.connect((self.blocks_sample_and_hold_xx_0, 0), (self.blks2_selector_0_1_0_0, 1))
        self.connect((self.blocks_sample_and_hold_xx_0, 0), (self.blocks_multiply_xx_0, 0))
        self.connect((self.blocks_threshold_ff_0, 0), (self.blocks_multiply_const_vxx_0_1_0, 0))
        self.connect((self.blocks_threshold_ff_0, 0), (self.blocks_multiply_xx_0, 1))
        self.connect((self.blocks_throttle_0_0, 0), (self.qtgui_freq_sink_x_0, 1))
        self.connect((self.blocks_throttle_0_0, 0), (self.qtgui_time_sink_x_0, 1))
        self.connect((self.blocks_throttle_0_0_0, 0), (self.qtgui_freq_sink_x_0, 2))
        self.connect((self.blocks_throttle_0_0_0, 0), (self.qtgui_time_sink_x_0, 2))
        self.connect((self.filtro_antialiasing, 0), (self.blks2_selector_0_1_0, 1))
        self.connect((self.filtro_antialiasing, 0), (self.blks2_selector_0_1_0_0, 0))
        self.connect((self.filtro_antialiasing, 0), (self.blocks_sample_and_hold_xx_0, 0))
        self.connect((self.low_pass_filter_0, 0), (self.blks2_selector_0_1_0_0_0_0, 1))
        self.connect((self.sen32, 0), (self.blocks_multiply_const_vxx_0_2, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_variable_qtgui_chooser_0(self):
        return self.variable_qtgui_chooser_0

    def set_variable_qtgui_chooser_0(self, variable_qtgui_chooser_0):
        self.variable_qtgui_chooser_0 = variable_qtgui_chooser_0
        self._variable_qtgui_chooser_0_callback(self.variable_qtgui_chooser_0)
        self.blks2_selector_0_1.set_input_index(int(self.variable_qtgui_chooser_0))

    def get_samplenholdcheck(self):
        return self.samplenholdcheck

    def set_samplenholdcheck(self, samplenholdcheck):
        self.samplenholdcheck = samplenholdcheck
        self._samplenholdcheck_callback(self.samplenholdcheck)
        self.blks2_selector_0_1_0_0.set_input_index(int(self.samplenholdcheck))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate)
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.fp, 2500, firdes.WIN_HAMMING, 6.76))
        self.filtro_antialiasing.set_taps(firdes.low_pass(1, self.samp_rate, self.fp, 2500, firdes.WIN_HAMMING, 6.76))
        self.blocks_throttle_0_0_0.set_sample_rate(self.samp_rate)
        self.blocks_throttle_0_0.set_sample_rate(self.samp_rate)
        self.analog_sig_source_x_0_2_1.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_2_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_2.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_0_0_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)

    def get_m(self):
        return self.m

    def set_m(self, m):
        self.m = m
        self.blocks_multiply_const_vxx_0_1.set_k((self.m/2, ))
        self.blocks_multiply_const_vxx_0_0.set_k((self.m/2, ))

    def get_llaveAnalcheck(self):
        return self.llaveAnalcheck

    def set_llaveAnalcheck(self, llaveAnalcheck):
        self.llaveAnalcheck = llaveAnalcheck
        self._llaveAnalcheck_callback(self.llaveAnalcheck)
        self.blks2_selector_0_1_0_0_0.set_input_index(int(self.llaveAnalcheck))

    def get_fportadora(self):
        return self.fportadora

    def set_fportadora(self, fportadora):
        self.fportadora = fportadora
        self.analog_sig_source_x_0_2_1.set_frequency(self.fportadora-self.fmoduladora)
        self.analog_sig_source_x_0_2_0.set_frequency(self.fportadora + self.fmoduladora)
        self.analog_sig_source_x_0_2.set_frequency(self.fportadora)

    def get_fp(self):
        return self.fp

    def set_fp(self, fp):
        self.fp = fp
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.fp, 2500, firdes.WIN_HAMMING, 6.76))
        self.filtro_antialiasing.set_taps(firdes.low_pass(1, self.samp_rate, self.fp, 2500, firdes.WIN_HAMMING, 6.76))

    def get_fmoduladora(self):
        return self.fmoduladora

    def set_fmoduladora(self, fmoduladora):
        self.fmoduladora = fmoduladora
        self.analog_sig_source_x_0_2_1.set_frequency(self.fportadora-self.fmoduladora)
        self.analog_sig_source_x_0_2_0.set_frequency(self.fportadora + self.fmoduladora)

    def get_faacheck(self):
        return self.faacheck

    def set_faacheck(self, faacheck):
        self.faacheck = faacheck
        self._faacheck_callback(self.faacheck)
        self.blks2_selector_0_1_0.set_input_index(int(self.faacheck))

    def get_dutycycle(self):
        return self.dutycycle

    def set_dutycycle(self, dutycycle):
        self.dutycycle = dutycycle
        self.blocks_threshold_ff_0.set_hi(1-self.dutycycle)
        self.blocks_threshold_ff_0.set_lo(1-self.dutycycle)

    def get_UIF(self):
        return self.UIF

    def set_UIF(self, UIF):
        self.UIF = UIF
        self.analog_sig_source_x_0_0.set_frequency(self.UIF)
        self.analog_sig_source_x_0.set_frequency(self.UIF)

    def get_SR(self):
        return self.SR

    def set_SR(self, SR):
        self.SR = SR
        self.analog_sig_source_x_0_0_0_0.set_frequency(self.SR)

    def get_FR(self):
        return self.FR

    def set_FR(self, FR):
        self.FR = FR
        self._FR_callback(self.FR)
        self.blks2_selector_0_1_0_0_0_0.set_input_index(int(self.FR))

    def get_AMPLITUD(self):
        return self.AMPLITUD

    def set_AMPLITUD(self, AMPLITUD):
        self.AMPLITUD = AMPLITUD
        self.blocks_multiply_const_vxx_0_2.set_k((self.AMPLITUD, ))
        self.analog_sig_source_x_0_2_1.set_amplitude(self.AMPLITUD)
        self.analog_sig_source_x_0_2_0.set_amplitude(self.AMPLITUD)
        self.analog_sig_source_x_0_2.set_amplitude(self.AMPLITUD)
        self.analog_sig_source_x_0_0.set_amplitude(self.AMPLITUD)
        self.analog_sig_source_x_0_0.set_offset(-self.AMPLITUD/2)
        self.analog_sig_source_x_0.set_amplitude(self.AMPLITUD)


def main(top_block_cls=top_block, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
